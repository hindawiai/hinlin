<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Microsemi Switchtec(पंचांग) PCIe Management Driver
 * Copyright (c) 2017, Microsemi Corporation
 */

#समावेश <linux/चयनtec.h>
#समावेश <linux/चयनtec_ioctl.h>

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/poll.h>
#समावेश <linux/रुको.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/nospec.h>

MODULE_DESCRIPTION("Microsemi Switchtec(tm) PCIe Management Driver");
MODULE_VERSION("0.1");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Microsemi Corporation");

अटल पूर्णांक max_devices = 16;
module_param(max_devices, पूर्णांक, 0644);
MODULE_PARM_DESC(max_devices, "max number of switchtec device instances");

अटल bool use_dma_mrpc = true;
module_param(use_dma_mrpc, bool, 0644);
MODULE_PARM_DESC(use_dma_mrpc,
		 "Enable the use of the DMA MRPC feature");

अटल पूर्णांक nirqs = 32;
module_param(nirqs, पूर्णांक, 0644);
MODULE_PARM_DESC(nirqs, "number of interrupts to allocate (more may be useful for NTB applications)");

अटल dev_t चयनtec_devt;
अटल DEFINE_IDA(चयनtec_minor_ida);

काष्ठा class *चयनtec_class;
EXPORT_SYMBOL_GPL(चयनtec_class);

क्रमागत mrpc_state अणु
	MRPC_IDLE = 0,
	MRPC_QUEUED,
	MRPC_RUNNING,
	MRPC_DONE,
पूर्ण;

काष्ठा चयनtec_user अणु
	काष्ठा चयनtec_dev *stdev;

	क्रमागत mrpc_state state;

	रुको_queue_head_t cmd_comp;
	काष्ठा kref kref;
	काष्ठा list_head list;

	bool cmd_करोne;
	u32 cmd;
	u32 status;
	u32 वापस_code;
	माप_प्रकार data_len;
	माप_प्रकार पढ़ो_len;
	अचिन्हित अक्षर data[SWITCHTEC_MRPC_PAYLOAD_SIZE];
	पूर्णांक event_cnt;
पूर्ण;

अटल काष्ठा चयनtec_user *stuser_create(काष्ठा चयनtec_dev *stdev)
अणु
	काष्ठा चयनtec_user *stuser;

	stuser = kzalloc(माप(*stuser), GFP_KERNEL);
	अगर (!stuser)
		वापस ERR_PTR(-ENOMEM);

	get_device(&stdev->dev);
	stuser->stdev = stdev;
	kref_init(&stuser->kref);
	INIT_LIST_HEAD(&stuser->list);
	init_रुकोqueue_head(&stuser->cmd_comp);
	stuser->event_cnt = atomic_पढ़ो(&stdev->event_cnt);

	dev_dbg(&stdev->dev, "%s: %p\n", __func__, stuser);

	वापस stuser;
पूर्ण

अटल व्योम stuser_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा चयनtec_user *stuser;

	stuser = container_of(kref, काष्ठा चयनtec_user, kref);

	dev_dbg(&stuser->stdev->dev, "%s: %p\n", __func__, stuser);

	put_device(&stuser->stdev->dev);
	kमुक्त(stuser);
पूर्ण

अटल व्योम stuser_put(काष्ठा चयनtec_user *stuser)
अणु
	kref_put(&stuser->kref, stuser_मुक्त);
पूर्ण

अटल व्योम stuser_set_state(काष्ठा चयनtec_user *stuser,
			     क्रमागत mrpc_state state)
अणु
	/* requires the mrpc_mutex to alपढ़ोy be held when called */

	स्थिर अक्षर * स्थिर state_names[] = अणु
		[MRPC_IDLE] = "IDLE",
		[MRPC_QUEUED] = "QUEUED",
		[MRPC_RUNNING] = "RUNNING",
		[MRPC_DONE] = "DONE",
	पूर्ण;

	stuser->state = state;

	dev_dbg(&stuser->stdev->dev, "stuser state %p -> %s",
		stuser, state_names[state]);
पूर्ण

अटल व्योम mrpc_complete_cmd(काष्ठा चयनtec_dev *stdev);

अटल व्योम flush_wc_buf(काष्ठा चयनtec_dev *stdev)
अणु
	काष्ठा ntb_dbmsg_regs __iomem *mmio_dbmsg;

	/*
	 * odb (outbound करोorbell) रेजिस्टर is processed by low latency
	 * hardware and w/o side effect
	 */
	mmio_dbmsg = (व्योम __iomem *)stdev->mmio_ntb +
		SWITCHTEC_NTB_REG_DBMSG_OFFSET;
	ioपढ़ो32(&mmio_dbmsg->odb);
पूर्ण

अटल व्योम mrpc_cmd_submit(काष्ठा चयनtec_dev *stdev)
अणु
	/* requires the mrpc_mutex to alपढ़ोy be held when called */

	काष्ठा चयनtec_user *stuser;

	अगर (stdev->mrpc_busy)
		वापस;

	अगर (list_empty(&stdev->mrpc_queue))
		वापस;

	stuser = list_entry(stdev->mrpc_queue.next, काष्ठा चयनtec_user,
			    list);

	अगर (stdev->dma_mrpc) अणु
		stdev->dma_mrpc->status = SWITCHTEC_MRPC_STATUS_INPROGRESS;
		स_रखो(stdev->dma_mrpc->data, 0xFF, SWITCHTEC_MRPC_PAYLOAD_SIZE);
	पूर्ण

	stuser_set_state(stuser, MRPC_RUNNING);
	stdev->mrpc_busy = 1;
	स_नकल_toio(&stdev->mmio_mrpc->input_data,
		    stuser->data, stuser->data_len);
	flush_wc_buf(stdev);
	ioग_लिखो32(stuser->cmd, &stdev->mmio_mrpc->cmd);

	schedule_delayed_work(&stdev->mrpc_समयout,
			      msecs_to_jअगरfies(500));
पूर्ण

अटल पूर्णांक mrpc_queue_cmd(काष्ठा चयनtec_user *stuser)
अणु
	/* requires the mrpc_mutex to alपढ़ोy be held when called */

	काष्ठा चयनtec_dev *stdev = stuser->stdev;

	kref_get(&stuser->kref);
	stuser->पढ़ो_len = माप(stuser->data);
	stuser_set_state(stuser, MRPC_QUEUED);
	stuser->cmd_करोne = false;
	list_add_tail(&stuser->list, &stdev->mrpc_queue);

	mrpc_cmd_submit(stdev);

	वापस 0;
पूर्ण

अटल व्योम mrpc_complete_cmd(काष्ठा चयनtec_dev *stdev)
अणु
	/* requires the mrpc_mutex to alपढ़ोy be held when called */
	काष्ठा चयनtec_user *stuser;

	अगर (list_empty(&stdev->mrpc_queue))
		वापस;

	stuser = list_entry(stdev->mrpc_queue.next, काष्ठा चयनtec_user,
			    list);

	अगर (stdev->dma_mrpc)
		stuser->status = stdev->dma_mrpc->status;
	अन्यथा
		stuser->status = ioपढ़ो32(&stdev->mmio_mrpc->status);

	अगर (stuser->status == SWITCHTEC_MRPC_STATUS_INPROGRESS)
		वापस;

	stuser_set_state(stuser, MRPC_DONE);
	stuser->वापस_code = 0;

	अगर (stuser->status != SWITCHTEC_MRPC_STATUS_DONE)
		जाओ out;

	अगर (stdev->dma_mrpc)
		stuser->वापस_code = stdev->dma_mrpc->rtn_code;
	अन्यथा
		stuser->वापस_code = ioपढ़ो32(&stdev->mmio_mrpc->ret_value);
	अगर (stuser->वापस_code != 0)
		जाओ out;

	अगर (stdev->dma_mrpc)
		स_नकल(stuser->data, &stdev->dma_mrpc->data,
			      stuser->पढ़ो_len);
	अन्यथा
		स_नकल_fromio(stuser->data, &stdev->mmio_mrpc->output_data,
			      stuser->पढ़ो_len);
out:
	stuser->cmd_करोne = true;
	wake_up_पूर्णांकerruptible(&stuser->cmd_comp);
	list_del_init(&stuser->list);
	stuser_put(stuser);
	stdev->mrpc_busy = 0;

	mrpc_cmd_submit(stdev);
पूर्ण

अटल व्योम mrpc_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा चयनtec_dev *stdev;

	stdev = container_of(work, काष्ठा चयनtec_dev, mrpc_work);

	dev_dbg(&stdev->dev, "%s\n", __func__);

	mutex_lock(&stdev->mrpc_mutex);
	cancel_delayed_work(&stdev->mrpc_समयout);
	mrpc_complete_cmd(stdev);
	mutex_unlock(&stdev->mrpc_mutex);
पूर्ण

अटल व्योम mrpc_समयout_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा चयनtec_dev *stdev;
	u32 status;

	stdev = container_of(work, काष्ठा चयनtec_dev, mrpc_समयout.work);

	dev_dbg(&stdev->dev, "%s\n", __func__);

	mutex_lock(&stdev->mrpc_mutex);

	अगर (stdev->dma_mrpc)
		status = stdev->dma_mrpc->status;
	अन्यथा
		status = ioपढ़ो32(&stdev->mmio_mrpc->status);
	अगर (status == SWITCHTEC_MRPC_STATUS_INPROGRESS) अणु
		schedule_delayed_work(&stdev->mrpc_समयout,
				      msecs_to_jअगरfies(500));
		जाओ out;
	पूर्ण

	mrpc_complete_cmd(stdev);
out:
	mutex_unlock(&stdev->mrpc_mutex);
पूर्ण

अटल sमाप_प्रकार device_version_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा चयनtec_dev *stdev = to_stdev(dev);
	u32 ver;

	ver = ioपढ़ो32(&stdev->mmio_sys_info->device_version);

	वापस प्र_लिखो(buf, "%x\n", ver);
पूर्ण
अटल DEVICE_ATTR_RO(device_version);

अटल sमाप_प्रकार fw_version_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा चयनtec_dev *stdev = to_stdev(dev);
	u32 ver;

	ver = ioपढ़ो32(&stdev->mmio_sys_info->firmware_version);

	वापस प्र_लिखो(buf, "%08x\n", ver);
पूर्ण
अटल DEVICE_ATTR_RO(fw_version);

अटल sमाप_प्रकार io_string_show(अक्षर *buf, व्योम __iomem *attr, माप_प्रकार len)
अणु
	पूर्णांक i;

	स_नकल_fromio(buf, attr, len);
	buf[len] = '\n';
	buf[len + 1] = 0;

	क्रम (i = len - 1; i > 0; i--) अणु
		अगर (buf[i] != ' ')
			अवरोध;
		buf[i] = '\n';
		buf[i + 1] = 0;
	पूर्ण

	वापस म_माप(buf);
पूर्ण

#घोषणा DEVICE_ATTR_SYS_INFO_STR(field) \
अटल sमाप_प्रकार field ## _show(काष्ठा device *dev, \
	काष्ठा device_attribute *attr, अक्षर *buf) \
अणु \
	काष्ठा चयनtec_dev *stdev = to_stdev(dev); \
	काष्ठा sys_info_regs __iomem *si = stdev->mmio_sys_info; \
	अगर (stdev->gen == SWITCHTEC_GEN3) \
		वापस io_string_show(buf, &si->gen3.field, \
				      माप(si->gen3.field)); \
	अन्यथा अगर (stdev->gen == SWITCHTEC_GEN4) \
		वापस io_string_show(buf, &si->gen4.field, \
				      माप(si->gen4.field)); \
	अन्यथा \
		वापस -ENOTSUPP; \
पूर्ण \
\
अटल DEVICE_ATTR_RO(field)

DEVICE_ATTR_SYS_INFO_STR(venकरोr_id);
DEVICE_ATTR_SYS_INFO_STR(product_id);
DEVICE_ATTR_SYS_INFO_STR(product_revision);

अटल sमाप_प्रकार component_venकरोr_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा चयनtec_dev *stdev = to_stdev(dev);
	काष्ठा sys_info_regs __iomem *si = stdev->mmio_sys_info;

	/* component_venकरोr field not supported after gen3 */
	अगर (stdev->gen != SWITCHTEC_GEN3)
		वापस प्र_लिखो(buf, "none\n");

	वापस io_string_show(buf, &si->gen3.component_venकरोr,
			      माप(si->gen3.component_venकरोr));
पूर्ण
अटल DEVICE_ATTR_RO(component_venकरोr);

अटल sमाप_प्रकार component_id_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा चयनtec_dev *stdev = to_stdev(dev);
	पूर्णांक id = ioपढ़ो16(&stdev->mmio_sys_info->gen3.component_id);

	/* component_id field not supported after gen3 */
	अगर (stdev->gen != SWITCHTEC_GEN3)
		वापस प्र_लिखो(buf, "none\n");

	वापस प्र_लिखो(buf, "PM%04X\n", id);
पूर्ण
अटल DEVICE_ATTR_RO(component_id);

अटल sमाप_प्रकार component_revision_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा चयनtec_dev *stdev = to_stdev(dev);
	पूर्णांक rev = ioपढ़ो8(&stdev->mmio_sys_info->gen3.component_revision);

	/* component_revision field not supported after gen3 */
	अगर (stdev->gen != SWITCHTEC_GEN3)
		वापस प्र_लिखो(buf, "255\n");

	वापस प्र_लिखो(buf, "%d\n", rev);
पूर्ण
अटल DEVICE_ATTR_RO(component_revision);

अटल sमाप_प्रकार partition_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा चयनtec_dev *stdev = to_stdev(dev);

	वापस प्र_लिखो(buf, "%d\n", stdev->partition);
पूर्ण
अटल DEVICE_ATTR_RO(partition);

अटल sमाप_प्रकार partition_count_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा चयनtec_dev *stdev = to_stdev(dev);

	वापस प्र_लिखो(buf, "%d\n", stdev->partition_count);
पूर्ण
अटल DEVICE_ATTR_RO(partition_count);

अटल काष्ठा attribute *चयनtec_device_attrs[] = अणु
	&dev_attr_device_version.attr,
	&dev_attr_fw_version.attr,
	&dev_attr_venकरोr_id.attr,
	&dev_attr_product_id.attr,
	&dev_attr_product_revision.attr,
	&dev_attr_component_venकरोr.attr,
	&dev_attr_component_id.attr,
	&dev_attr_component_revision.attr,
	&dev_attr_partition.attr,
	&dev_attr_partition_count.attr,
	शून्य,
पूर्ण;

ATTRIBUTE_GROUPS(चयनtec_device);

अटल पूर्णांक चयनtec_dev_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा चयनtec_dev *stdev;
	काष्ठा चयनtec_user *stuser;

	stdev = container_of(inode->i_cdev, काष्ठा चयनtec_dev, cdev);

	stuser = stuser_create(stdev);
	अगर (IS_ERR(stuser))
		वापस PTR_ERR(stuser);

	filp->निजी_data = stuser;
	stream_खोलो(inode, filp);

	dev_dbg(&stdev->dev, "%s: %p\n", __func__, stuser);

	वापस 0;
पूर्ण

अटल पूर्णांक चयनtec_dev_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा चयनtec_user *stuser = filp->निजी_data;

	stuser_put(stuser);

	वापस 0;
पूर्ण

अटल पूर्णांक lock_mutex_and_test_alive(काष्ठा चयनtec_dev *stdev)
अणु
	अगर (mutex_lock_पूर्णांकerruptible(&stdev->mrpc_mutex))
		वापस -EINTR;

	अगर (!stdev->alive) अणु
		mutex_unlock(&stdev->mrpc_mutex);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार चयनtec_dev_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *data,
				   माप_प्रकार size, loff_t *off)
अणु
	काष्ठा चयनtec_user *stuser = filp->निजी_data;
	काष्ठा चयनtec_dev *stdev = stuser->stdev;
	पूर्णांक rc;

	अगर (size < माप(stuser->cmd) ||
	    size > माप(stuser->cmd) + माप(stuser->data))
		वापस -EINVAL;

	stuser->data_len = size - माप(stuser->cmd);

	rc = lock_mutex_and_test_alive(stdev);
	अगर (rc)
		वापस rc;

	अगर (stuser->state != MRPC_IDLE) अणु
		rc = -EBADE;
		जाओ out;
	पूर्ण

	rc = copy_from_user(&stuser->cmd, data, माप(stuser->cmd));
	अगर (rc) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण
	अगर (((MRPC_CMD_ID(stuser->cmd) == MRPC_GAS_WRITE) ||
	     (MRPC_CMD_ID(stuser->cmd) == MRPC_GAS_READ)) &&
	    !capable(CAP_SYS_ADMIN)) अणु
		rc = -EPERM;
		जाओ out;
	पूर्ण

	data += माप(stuser->cmd);
	rc = copy_from_user(&stuser->data, data, size - माप(stuser->cmd));
	अगर (rc) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	rc = mrpc_queue_cmd(stuser);

out:
	mutex_unlock(&stdev->mrpc_mutex);

	अगर (rc)
		वापस rc;

	वापस size;
पूर्ण

अटल sमाप_प्रकार चयनtec_dev_पढ़ो(काष्ठा file *filp, अक्षर __user *data,
				  माप_प्रकार size, loff_t *off)
अणु
	काष्ठा चयनtec_user *stuser = filp->निजी_data;
	काष्ठा चयनtec_dev *stdev = stuser->stdev;
	पूर्णांक rc;

	अगर (size < माप(stuser->cmd) ||
	    size > माप(stuser->cmd) + माप(stuser->data))
		वापस -EINVAL;

	rc = lock_mutex_and_test_alive(stdev);
	अगर (rc)
		वापस rc;

	अगर (stuser->state == MRPC_IDLE) अणु
		mutex_unlock(&stdev->mrpc_mutex);
		वापस -EBADE;
	पूर्ण

	stuser->पढ़ो_len = size - माप(stuser->वापस_code);

	mutex_unlock(&stdev->mrpc_mutex);

	अगर (filp->f_flags & O_NONBLOCK) अणु
		अगर (!stuser->cmd_करोne)
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		rc = रुको_event_पूर्णांकerruptible(stuser->cmd_comp,
					      stuser->cmd_करोne);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	rc = lock_mutex_and_test_alive(stdev);
	अगर (rc)
		वापस rc;

	अगर (stuser->state != MRPC_DONE) अणु
		mutex_unlock(&stdev->mrpc_mutex);
		वापस -EBADE;
	पूर्ण

	rc = copy_to_user(data, &stuser->वापस_code,
			  माप(stuser->वापस_code));
	अगर (rc) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	data += माप(stuser->वापस_code);
	rc = copy_to_user(data, &stuser->data,
			  size - माप(stuser->वापस_code));
	अगर (rc) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	stuser_set_state(stuser, MRPC_IDLE);

out:
	mutex_unlock(&stdev->mrpc_mutex);

	अगर (stuser->status == SWITCHTEC_MRPC_STATUS_DONE)
		वापस size;
	अन्यथा अगर (stuser->status == SWITCHTEC_MRPC_STATUS_INTERRUPTED)
		वापस -ENXIO;
	अन्यथा
		वापस -EBADMSG;
पूर्ण

अटल __poll_t चयनtec_dev_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा चयनtec_user *stuser = filp->निजी_data;
	काष्ठा चयनtec_dev *stdev = stuser->stdev;
	__poll_t ret = 0;

	poll_रुको(filp, &stuser->cmd_comp, रुको);
	poll_रुको(filp, &stdev->event_wq, रुको);

	अगर (lock_mutex_and_test_alive(stdev))
		वापस EPOLLIN | EPOLLRDHUP | EPOLLOUT | EPOLLERR | EPOLLHUP;

	mutex_unlock(&stdev->mrpc_mutex);

	अगर (stuser->cmd_करोne)
		ret |= EPOLLIN | EPOLLRDNORM;

	अगर (stuser->event_cnt != atomic_पढ़ो(&stdev->event_cnt))
		ret |= EPOLLPRI | EPOLLRDBAND;

	वापस ret;
पूर्ण

अटल पूर्णांक ioctl_flash_info(काष्ठा चयनtec_dev *stdev,
			    काष्ठा चयनtec_ioctl_flash_info __user *uinfo)
अणु
	काष्ठा चयनtec_ioctl_flash_info info = अणु0पूर्ण;
	काष्ठा flash_info_regs __iomem *fi = stdev->mmio_flash_info;

	अगर (stdev->gen == SWITCHTEC_GEN3) अणु
		info.flash_length = ioपढ़ो32(&fi->gen3.flash_length);
		info.num_partitions = SWITCHTEC_NUM_PARTITIONS_GEN3;
	पूर्ण अन्यथा अगर (stdev->gen == SWITCHTEC_GEN4) अणु
		info.flash_length = ioपढ़ो32(&fi->gen4.flash_length);
		info.num_partitions = SWITCHTEC_NUM_PARTITIONS_GEN4;
	पूर्ण अन्यथा अणु
		वापस -ENOTSUPP;
	पूर्ण

	अगर (copy_to_user(uinfo, &info, माप(info)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल व्योम set_fw_info_part(काष्ठा चयनtec_ioctl_flash_part_info *info,
			     काष्ठा partition_info __iomem *pi)
अणु
	info->address = ioपढ़ो32(&pi->address);
	info->length = ioपढ़ो32(&pi->length);
पूर्ण

अटल पूर्णांक flash_part_info_gen3(काष्ठा चयनtec_dev *stdev,
		काष्ठा चयनtec_ioctl_flash_part_info *info)
अणु
	काष्ठा flash_info_regs_gen3 __iomem *fi =
		&stdev->mmio_flash_info->gen3;
	काष्ठा sys_info_regs_gen3 __iomem *si = &stdev->mmio_sys_info->gen3;
	u32 active_addr = -1;

	चयन (info->flash_partition) अणु
	हाल SWITCHTEC_IOCTL_PART_CFG0:
		active_addr = ioपढ़ो32(&fi->active_cfg);
		set_fw_info_part(info, &fi->cfg0);
		अगर (ioपढ़ो16(&si->cfg_running) == SWITCHTEC_GEN3_CFG0_RUNNING)
			info->active |= SWITCHTEC_IOCTL_PART_RUNNING;
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_CFG1:
		active_addr = ioपढ़ो32(&fi->active_cfg);
		set_fw_info_part(info, &fi->cfg1);
		अगर (ioपढ़ो16(&si->cfg_running) == SWITCHTEC_GEN3_CFG1_RUNNING)
			info->active |= SWITCHTEC_IOCTL_PART_RUNNING;
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_IMG0:
		active_addr = ioपढ़ो32(&fi->active_img);
		set_fw_info_part(info, &fi->img0);
		अगर (ioपढ़ो16(&si->img_running) == SWITCHTEC_GEN3_IMG0_RUNNING)
			info->active |= SWITCHTEC_IOCTL_PART_RUNNING;
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_IMG1:
		active_addr = ioपढ़ो32(&fi->active_img);
		set_fw_info_part(info, &fi->img1);
		अगर (ioपढ़ो16(&si->img_running) == SWITCHTEC_GEN3_IMG1_RUNNING)
			info->active |= SWITCHTEC_IOCTL_PART_RUNNING;
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_NVLOG:
		set_fw_info_part(info, &fi->nvlog);
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_VENDOR0:
		set_fw_info_part(info, &fi->venकरोr[0]);
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_VENDOR1:
		set_fw_info_part(info, &fi->venकरोr[1]);
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_VENDOR2:
		set_fw_info_part(info, &fi->venकरोr[2]);
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_VENDOR3:
		set_fw_info_part(info, &fi->venकरोr[3]);
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_VENDOR4:
		set_fw_info_part(info, &fi->venकरोr[4]);
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_VENDOR5:
		set_fw_info_part(info, &fi->venकरोr[5]);
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_VENDOR6:
		set_fw_info_part(info, &fi->venकरोr[6]);
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_VENDOR7:
		set_fw_info_part(info, &fi->venकरोr[7]);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (info->address == active_addr)
		info->active |= SWITCHTEC_IOCTL_PART_ACTIVE;

	वापस 0;
पूर्ण

अटल पूर्णांक flash_part_info_gen4(काष्ठा चयनtec_dev *stdev,
		काष्ठा चयनtec_ioctl_flash_part_info *info)
अणु
	काष्ठा flash_info_regs_gen4 __iomem *fi = &stdev->mmio_flash_info->gen4;
	काष्ठा sys_info_regs_gen4 __iomem *si = &stdev->mmio_sys_info->gen4;
	काष्ठा active_partition_info_gen4 __iomem *af = &fi->active_flag;

	चयन (info->flash_partition) अणु
	हाल SWITCHTEC_IOCTL_PART_MAP_0:
		set_fw_info_part(info, &fi->map0);
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_MAP_1:
		set_fw_info_part(info, &fi->map1);
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_KEY_0:
		set_fw_info_part(info, &fi->key0);
		अगर (ioपढ़ो8(&af->key) == SWITCHTEC_GEN4_KEY0_ACTIVE)
			info->active |= SWITCHTEC_IOCTL_PART_ACTIVE;
		अगर (ioपढ़ो16(&si->key_running) == SWITCHTEC_GEN4_KEY0_RUNNING)
			info->active |= SWITCHTEC_IOCTL_PART_RUNNING;
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_KEY_1:
		set_fw_info_part(info, &fi->key1);
		अगर (ioपढ़ो8(&af->key) == SWITCHTEC_GEN4_KEY1_ACTIVE)
			info->active |= SWITCHTEC_IOCTL_PART_ACTIVE;
		अगर (ioपढ़ो16(&si->key_running) == SWITCHTEC_GEN4_KEY1_RUNNING)
			info->active |= SWITCHTEC_IOCTL_PART_RUNNING;
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_BL2_0:
		set_fw_info_part(info, &fi->bl2_0);
		अगर (ioपढ़ो8(&af->bl2) == SWITCHTEC_GEN4_BL2_0_ACTIVE)
			info->active |= SWITCHTEC_IOCTL_PART_ACTIVE;
		अगर (ioपढ़ो16(&si->bl2_running) == SWITCHTEC_GEN4_BL2_0_RUNNING)
			info->active |= SWITCHTEC_IOCTL_PART_RUNNING;
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_BL2_1:
		set_fw_info_part(info, &fi->bl2_1);
		अगर (ioपढ़ो8(&af->bl2) == SWITCHTEC_GEN4_BL2_1_ACTIVE)
			info->active |= SWITCHTEC_IOCTL_PART_ACTIVE;
		अगर (ioपढ़ो16(&si->bl2_running) == SWITCHTEC_GEN4_BL2_1_RUNNING)
			info->active |= SWITCHTEC_IOCTL_PART_RUNNING;
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_CFG0:
		set_fw_info_part(info, &fi->cfg0);
		अगर (ioपढ़ो8(&af->cfg) == SWITCHTEC_GEN4_CFG0_ACTIVE)
			info->active |= SWITCHTEC_IOCTL_PART_ACTIVE;
		अगर (ioपढ़ो16(&si->cfg_running) == SWITCHTEC_GEN4_CFG0_RUNNING)
			info->active |= SWITCHTEC_IOCTL_PART_RUNNING;
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_CFG1:
		set_fw_info_part(info, &fi->cfg1);
		अगर (ioपढ़ो8(&af->cfg) == SWITCHTEC_GEN4_CFG1_ACTIVE)
			info->active |= SWITCHTEC_IOCTL_PART_ACTIVE;
		अगर (ioपढ़ो16(&si->cfg_running) == SWITCHTEC_GEN4_CFG1_RUNNING)
			info->active |= SWITCHTEC_IOCTL_PART_RUNNING;
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_IMG0:
		set_fw_info_part(info, &fi->img0);
		अगर (ioपढ़ो8(&af->img) == SWITCHTEC_GEN4_IMG0_ACTIVE)
			info->active |= SWITCHTEC_IOCTL_PART_ACTIVE;
		अगर (ioपढ़ो16(&si->img_running) == SWITCHTEC_GEN4_IMG0_RUNNING)
			info->active |= SWITCHTEC_IOCTL_PART_RUNNING;
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_IMG1:
		set_fw_info_part(info, &fi->img1);
		अगर (ioपढ़ो8(&af->img) == SWITCHTEC_GEN4_IMG1_ACTIVE)
			info->active |= SWITCHTEC_IOCTL_PART_ACTIVE;
		अगर (ioपढ़ो16(&si->img_running) == SWITCHTEC_GEN4_IMG1_RUNNING)
			info->active |= SWITCHTEC_IOCTL_PART_RUNNING;
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_NVLOG:
		set_fw_info_part(info, &fi->nvlog);
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_VENDOR0:
		set_fw_info_part(info, &fi->venकरोr[0]);
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_VENDOR1:
		set_fw_info_part(info, &fi->venकरोr[1]);
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_VENDOR2:
		set_fw_info_part(info, &fi->venकरोr[2]);
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_VENDOR3:
		set_fw_info_part(info, &fi->venकरोr[3]);
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_VENDOR4:
		set_fw_info_part(info, &fi->venकरोr[4]);
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_VENDOR5:
		set_fw_info_part(info, &fi->venकरोr[5]);
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_VENDOR6:
		set_fw_info_part(info, &fi->venकरोr[6]);
		अवरोध;
	हाल SWITCHTEC_IOCTL_PART_VENDOR7:
		set_fw_info_part(info, &fi->venकरोr[7]);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ioctl_flash_part_info(काष्ठा चयनtec_dev *stdev,
		काष्ठा चयनtec_ioctl_flash_part_info __user *uinfo)
अणु
	पूर्णांक ret;
	काष्ठा चयनtec_ioctl_flash_part_info info = अणु0पूर्ण;

	अगर (copy_from_user(&info, uinfo, माप(info)))
		वापस -EFAULT;

	अगर (stdev->gen == SWITCHTEC_GEN3) अणु
		ret = flash_part_info_gen3(stdev, &info);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अगर (stdev->gen == SWITCHTEC_GEN4) अणु
		ret = flash_part_info_gen4(stdev, &info);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		वापस -ENOTSUPP;
	पूर्ण

	अगर (copy_to_user(uinfo, &info, माप(info)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक ioctl_event_summary(काष्ठा चयनtec_dev *stdev,
	काष्ठा चयनtec_user *stuser,
	काष्ठा चयनtec_ioctl_event_summary __user *usum,
	माप_प्रकार size)
अणु
	काष्ठा चयनtec_ioctl_event_summary *s;
	पूर्णांक i;
	u32 reg;
	पूर्णांक ret = 0;

	s = kzalloc(माप(*s), GFP_KERNEL);
	अगर (!s)
		वापस -ENOMEM;

	s->global = ioपढ़ो32(&stdev->mmio_sw_event->global_summary);
	s->part_biपंचांगap = ioपढ़ो64(&stdev->mmio_sw_event->part_event_biपंचांगap);
	s->local_part = ioपढ़ो32(&stdev->mmio_part_cfg->part_event_summary);

	क्रम (i = 0; i < stdev->partition_count; i++) अणु
		reg = ioपढ़ो32(&stdev->mmio_part_cfg_all[i].part_event_summary);
		s->part[i] = reg;
	पूर्ण

	क्रम (i = 0; i < stdev->pff_csr_count; i++) अणु
		reg = ioपढ़ो32(&stdev->mmio_pff_csr[i].pff_event_summary);
		s->pff[i] = reg;
	पूर्ण

	अगर (copy_to_user(usum, s, size)) अणु
		ret = -EFAULT;
		जाओ error_हाल;
	पूर्ण

	stuser->event_cnt = atomic_पढ़ो(&stdev->event_cnt);

error_हाल:
	kमुक्त(s);
	वापस ret;
पूर्ण

अटल u32 __iomem *global_ev_reg(काष्ठा चयनtec_dev *stdev,
				  माप_प्रकार offset, पूर्णांक index)
अणु
	वापस (व्योम __iomem *)stdev->mmio_sw_event + offset;
पूर्ण

अटल u32 __iomem *part_ev_reg(काष्ठा चयनtec_dev *stdev,
				माप_प्रकार offset, पूर्णांक index)
अणु
	वापस (व्योम __iomem *)&stdev->mmio_part_cfg_all[index] + offset;
पूर्ण

अटल u32 __iomem *pff_ev_reg(काष्ठा चयनtec_dev *stdev,
			       माप_प्रकार offset, पूर्णांक index)
अणु
	वापस (व्योम __iomem *)&stdev->mmio_pff_csr[index] + offset;
पूर्ण

#घोषणा EV_GLB(i, r)[i] = अणुदुरत्व(काष्ठा sw_event_regs, r), global_ev_regपूर्ण
#घोषणा EV_PAR(i, r)[i] = अणुदुरत्व(काष्ठा part_cfg_regs, r), part_ev_regपूर्ण
#घोषणा EV_PFF(i, r)[i] = अणुदुरत्व(काष्ठा pff_csr_regs, r), pff_ev_regपूर्ण

अटल स्थिर काष्ठा event_reg अणु
	माप_प्रकार offset;
	u32 __iomem *(*map_reg)(काष्ठा चयनtec_dev *stdev,
				माप_प्रकार offset, पूर्णांक index);
पूर्ण event_regs[] = अणु
	EV_GLB(SWITCHTEC_IOCTL_EVENT_STACK_ERROR, stack_error_event_hdr),
	EV_GLB(SWITCHTEC_IOCTL_EVENT_PPU_ERROR, ppu_error_event_hdr),
	EV_GLB(SWITCHTEC_IOCTL_EVENT_ISP_ERROR, isp_error_event_hdr),
	EV_GLB(SWITCHTEC_IOCTL_EVENT_SYS_RESET, sys_reset_event_hdr),
	EV_GLB(SWITCHTEC_IOCTL_EVENT_FW_EXC, fw_exception_hdr),
	EV_GLB(SWITCHTEC_IOCTL_EVENT_FW_NMI, fw_nmi_hdr),
	EV_GLB(SWITCHTEC_IOCTL_EVENT_FW_NON_FATAL, fw_non_fatal_hdr),
	EV_GLB(SWITCHTEC_IOCTL_EVENT_FW_FATAL, fw_fatal_hdr),
	EV_GLB(SWITCHTEC_IOCTL_EVENT_TWI_MRPC_COMP, twi_mrpc_comp_hdr),
	EV_GLB(SWITCHTEC_IOCTL_EVENT_TWI_MRPC_COMP_ASYNC,
	       twi_mrpc_comp_async_hdr),
	EV_GLB(SWITCHTEC_IOCTL_EVENT_CLI_MRPC_COMP, cli_mrpc_comp_hdr),
	EV_GLB(SWITCHTEC_IOCTL_EVENT_CLI_MRPC_COMP_ASYNC,
	       cli_mrpc_comp_async_hdr),
	EV_GLB(SWITCHTEC_IOCTL_EVENT_GPIO_INT, gpio_पूर्णांकerrupt_hdr),
	EV_GLB(SWITCHTEC_IOCTL_EVENT_GFMS, gfms_event_hdr),
	EV_PAR(SWITCHTEC_IOCTL_EVENT_PART_RESET, part_reset_hdr),
	EV_PAR(SWITCHTEC_IOCTL_EVENT_MRPC_COMP, mrpc_comp_hdr),
	EV_PAR(SWITCHTEC_IOCTL_EVENT_MRPC_COMP_ASYNC, mrpc_comp_async_hdr),
	EV_PAR(SWITCHTEC_IOCTL_EVENT_DYN_PART_BIND_COMP, dyn_binding_hdr),
	EV_PAR(SWITCHTEC_IOCTL_EVENT_INTERCOMM_REQ_NOTIFY,
	       पूर्णांकercomm_notअगरy_hdr),
	EV_PFF(SWITCHTEC_IOCTL_EVENT_AER_IN_P2P, aer_in_p2p_hdr),
	EV_PFF(SWITCHTEC_IOCTL_EVENT_AER_IN_VEP, aer_in_vep_hdr),
	EV_PFF(SWITCHTEC_IOCTL_EVENT_DPC, dpc_hdr),
	EV_PFF(SWITCHTEC_IOCTL_EVENT_CTS, cts_hdr),
	EV_PFF(SWITCHTEC_IOCTL_EVENT_UEC, uec_hdr),
	EV_PFF(SWITCHTEC_IOCTL_EVENT_HOTPLUG, hotplug_hdr),
	EV_PFF(SWITCHTEC_IOCTL_EVENT_IER, ier_hdr),
	EV_PFF(SWITCHTEC_IOCTL_EVENT_THRESH, threshold_hdr),
	EV_PFF(SWITCHTEC_IOCTL_EVENT_POWER_MGMT, घातer_mgmt_hdr),
	EV_PFF(SWITCHTEC_IOCTL_EVENT_TLP_THROTTLING, tlp_throttling_hdr),
	EV_PFF(SWITCHTEC_IOCTL_EVENT_FORCE_SPEED, क्रमce_speed_hdr),
	EV_PFF(SWITCHTEC_IOCTL_EVENT_CREDIT_TIMEOUT, credit_समयout_hdr),
	EV_PFF(SWITCHTEC_IOCTL_EVENT_LINK_STATE, link_state_hdr),
पूर्ण;

अटल u32 __iomem *event_hdr_addr(काष्ठा चयनtec_dev *stdev,
				   पूर्णांक event_id, पूर्णांक index)
अणु
	माप_प्रकार off;

	अगर (event_id < 0 || event_id >= SWITCHTEC_IOCTL_MAX_EVENTS)
		वापस (u32 __iomem *)ERR_PTR(-EINVAL);

	off = event_regs[event_id].offset;

	अगर (event_regs[event_id].map_reg == part_ev_reg) अणु
		अगर (index == SWITCHTEC_IOCTL_EVENT_LOCAL_PART_IDX)
			index = stdev->partition;
		अन्यथा अगर (index < 0 || index >= stdev->partition_count)
			वापस (u32 __iomem *)ERR_PTR(-EINVAL);
	पूर्ण अन्यथा अगर (event_regs[event_id].map_reg == pff_ev_reg) अणु
		अगर (index < 0 || index >= stdev->pff_csr_count)
			वापस (u32 __iomem *)ERR_PTR(-EINVAL);
	पूर्ण

	वापस event_regs[event_id].map_reg(stdev, off, index);
पूर्ण

अटल पूर्णांक event_ctl(काष्ठा चयनtec_dev *stdev,
		     काष्ठा चयनtec_ioctl_event_ctl *ctl)
अणु
	पूर्णांक i;
	u32 __iomem *reg;
	u32 hdr;

	reg = event_hdr_addr(stdev, ctl->event_id, ctl->index);
	अगर (IS_ERR(reg))
		वापस PTR_ERR(reg);

	hdr = ioपढ़ो32(reg);
	क्रम (i = 0; i < ARRAY_SIZE(ctl->data); i++)
		ctl->data[i] = ioपढ़ो32(&reg[i + 1]);

	ctl->occurred = hdr & SWITCHTEC_EVENT_OCCURRED;
	ctl->count = (hdr >> 5) & 0xFF;

	अगर (!(ctl->flags & SWITCHTEC_IOCTL_EVENT_FLAG_CLEAR))
		hdr &= ~SWITCHTEC_EVENT_CLEAR;
	अगर (ctl->flags & SWITCHTEC_IOCTL_EVENT_FLAG_EN_POLL)
		hdr |= SWITCHTEC_EVENT_EN_IRQ;
	अगर (ctl->flags & SWITCHTEC_IOCTL_EVENT_FLAG_DIS_POLL)
		hdr &= ~SWITCHTEC_EVENT_EN_IRQ;
	अगर (ctl->flags & SWITCHTEC_IOCTL_EVENT_FLAG_EN_LOG)
		hdr |= SWITCHTEC_EVENT_EN_LOG;
	अगर (ctl->flags & SWITCHTEC_IOCTL_EVENT_FLAG_DIS_LOG)
		hdr &= ~SWITCHTEC_EVENT_EN_LOG;
	अगर (ctl->flags & SWITCHTEC_IOCTL_EVENT_FLAG_EN_CLI)
		hdr |= SWITCHTEC_EVENT_EN_CLI;
	अगर (ctl->flags & SWITCHTEC_IOCTL_EVENT_FLAG_DIS_CLI)
		hdr &= ~SWITCHTEC_EVENT_EN_CLI;
	अगर (ctl->flags & SWITCHTEC_IOCTL_EVENT_FLAG_EN_FATAL)
		hdr |= SWITCHTEC_EVENT_FATAL;
	अगर (ctl->flags & SWITCHTEC_IOCTL_EVENT_FLAG_DIS_FATAL)
		hdr &= ~SWITCHTEC_EVENT_FATAL;

	अगर (ctl->flags)
		ioग_लिखो32(hdr, reg);

	ctl->flags = 0;
	अगर (hdr & SWITCHTEC_EVENT_EN_IRQ)
		ctl->flags |= SWITCHTEC_IOCTL_EVENT_FLAG_EN_POLL;
	अगर (hdr & SWITCHTEC_EVENT_EN_LOG)
		ctl->flags |= SWITCHTEC_IOCTL_EVENT_FLAG_EN_LOG;
	अगर (hdr & SWITCHTEC_EVENT_EN_CLI)
		ctl->flags |= SWITCHTEC_IOCTL_EVENT_FLAG_EN_CLI;
	अगर (hdr & SWITCHTEC_EVENT_FATAL)
		ctl->flags |= SWITCHTEC_IOCTL_EVENT_FLAG_EN_FATAL;

	वापस 0;
पूर्ण

अटल पूर्णांक ioctl_event_ctl(काष्ठा चयनtec_dev *stdev,
	काष्ठा चयनtec_ioctl_event_ctl __user *uctl)
अणु
	पूर्णांक ret;
	पूर्णांक nr_idxs;
	अचिन्हित पूर्णांक event_flags;
	काष्ठा चयनtec_ioctl_event_ctl ctl;

	अगर (copy_from_user(&ctl, uctl, माप(ctl)))
		वापस -EFAULT;

	अगर (ctl.event_id >= SWITCHTEC_IOCTL_MAX_EVENTS)
		वापस -EINVAL;

	अगर (ctl.flags & SWITCHTEC_IOCTL_EVENT_FLAG_UNUSED)
		वापस -EINVAL;

	अगर (ctl.index == SWITCHTEC_IOCTL_EVENT_IDX_ALL) अणु
		अगर (event_regs[ctl.event_id].map_reg == global_ev_reg)
			nr_idxs = 1;
		अन्यथा अगर (event_regs[ctl.event_id].map_reg == part_ev_reg)
			nr_idxs = stdev->partition_count;
		अन्यथा अगर (event_regs[ctl.event_id].map_reg == pff_ev_reg)
			nr_idxs = stdev->pff_csr_count;
		अन्यथा
			वापस -EINVAL;

		event_flags = ctl.flags;
		क्रम (ctl.index = 0; ctl.index < nr_idxs; ctl.index++) अणु
			ctl.flags = event_flags;
			ret = event_ctl(stdev, &ctl);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = event_ctl(stdev, &ctl);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (copy_to_user(uctl, &ctl, माप(ctl)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक ioctl_pff_to_port(काष्ठा चयनtec_dev *stdev,
			     काष्ठा चयनtec_ioctl_pff_port __user *up)
अणु
	पूर्णांक i, part;
	u32 reg;
	काष्ठा part_cfg_regs __iomem *pcfg;
	काष्ठा चयनtec_ioctl_pff_port p;

	अगर (copy_from_user(&p, up, माप(p)))
		वापस -EFAULT;

	p.port = -1;
	क्रम (part = 0; part < stdev->partition_count; part++) अणु
		pcfg = &stdev->mmio_part_cfg_all[part];
		p.partition = part;

		reg = ioपढ़ो32(&pcfg->usp_pff_inst_id);
		अगर (reg == p.pff) अणु
			p.port = 0;
			अवरोध;
		पूर्ण

		reg = ioपढ़ो32(&pcfg->vep_pff_inst_id);
		अगर (reg == p.pff) अणु
			p.port = SWITCHTEC_IOCTL_PFF_VEP;
			अवरोध;
		पूर्ण

		क्रम (i = 0; i < ARRAY_SIZE(pcfg->dsp_pff_inst_id); i++) अणु
			reg = ioपढ़ो32(&pcfg->dsp_pff_inst_id[i]);
			अगर (reg != p.pff)
				जारी;

			p.port = i + 1;
			अवरोध;
		पूर्ण

		अगर (p.port != -1)
			अवरोध;
	पूर्ण

	अगर (copy_to_user(up, &p, माप(p)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक ioctl_port_to_pff(काष्ठा चयनtec_dev *stdev,
			     काष्ठा चयनtec_ioctl_pff_port __user *up)
अणु
	काष्ठा चयनtec_ioctl_pff_port p;
	काष्ठा part_cfg_regs __iomem *pcfg;

	अगर (copy_from_user(&p, up, माप(p)))
		वापस -EFAULT;

	अगर (p.partition == SWITCHTEC_IOCTL_EVENT_LOCAL_PART_IDX)
		pcfg = stdev->mmio_part_cfg;
	अन्यथा अगर (p.partition < stdev->partition_count)
		pcfg = &stdev->mmio_part_cfg_all[p.partition];
	अन्यथा
		वापस -EINVAL;

	चयन (p.port) अणु
	हाल 0:
		p.pff = ioपढ़ो32(&pcfg->usp_pff_inst_id);
		अवरोध;
	हाल SWITCHTEC_IOCTL_PFF_VEP:
		p.pff = ioपढ़ो32(&pcfg->vep_pff_inst_id);
		अवरोध;
	शेष:
		अगर (p.port > ARRAY_SIZE(pcfg->dsp_pff_inst_id))
			वापस -EINVAL;
		p.port = array_index_nospec(p.port,
					ARRAY_SIZE(pcfg->dsp_pff_inst_id) + 1);
		p.pff = ioपढ़ो32(&pcfg->dsp_pff_inst_id[p.port - 1]);
		अवरोध;
	पूर्ण

	अगर (copy_to_user(up, &p, माप(p)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल दीर्घ चयनtec_dev_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	काष्ठा चयनtec_user *stuser = filp->निजी_data;
	काष्ठा चयनtec_dev *stdev = stuser->stdev;
	पूर्णांक rc;
	व्योम __user *argp = (व्योम __user *)arg;

	rc = lock_mutex_and_test_alive(stdev);
	अगर (rc)
		वापस rc;

	चयन (cmd) अणु
	हाल SWITCHTEC_IOCTL_FLASH_INFO:
		rc = ioctl_flash_info(stdev, argp);
		अवरोध;
	हाल SWITCHTEC_IOCTL_FLASH_PART_INFO:
		rc = ioctl_flash_part_info(stdev, argp);
		अवरोध;
	हाल SWITCHTEC_IOCTL_EVENT_SUMMARY_LEGACY:
		rc = ioctl_event_summary(stdev, stuser, argp,
					 माप(काष्ठा चयनtec_ioctl_event_summary_legacy));
		अवरोध;
	हाल SWITCHTEC_IOCTL_EVENT_CTL:
		rc = ioctl_event_ctl(stdev, argp);
		अवरोध;
	हाल SWITCHTEC_IOCTL_PFF_TO_PORT:
		rc = ioctl_pff_to_port(stdev, argp);
		अवरोध;
	हाल SWITCHTEC_IOCTL_PORT_TO_PFF:
		rc = ioctl_port_to_pff(stdev, argp);
		अवरोध;
	हाल SWITCHTEC_IOCTL_EVENT_SUMMARY:
		rc = ioctl_event_summary(stdev, stuser, argp,
					 माप(काष्ठा चयनtec_ioctl_event_summary));
		अवरोध;
	शेष:
		rc = -ENOTTY;
		अवरोध;
	पूर्ण

	mutex_unlock(&stdev->mrpc_mutex);
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा file_operations चयनtec_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = चयनtec_dev_खोलो,
	.release = चयनtec_dev_release,
	.ग_लिखो = चयनtec_dev_ग_लिखो,
	.पढ़ो = चयनtec_dev_पढ़ो,
	.poll = चयनtec_dev_poll,
	.unlocked_ioctl = चयनtec_dev_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
पूर्ण;

अटल व्योम link_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा चयनtec_dev *stdev;

	stdev = container_of(work, काष्ठा चयनtec_dev, link_event_work);

	अगर (stdev->link_notअगरier)
		stdev->link_notअगरier(stdev);
पूर्ण

अटल व्योम check_link_state_events(काष्ठा चयनtec_dev *stdev)
अणु
	पूर्णांक idx;
	u32 reg;
	पूर्णांक count;
	पूर्णांक occurred = 0;

	क्रम (idx = 0; idx < stdev->pff_csr_count; idx++) अणु
		reg = ioपढ़ो32(&stdev->mmio_pff_csr[idx].link_state_hdr);
		dev_dbg(&stdev->dev, "link_state: %d->%08x\n", idx, reg);
		count = (reg >> 5) & 0xFF;

		अगर (count != stdev->link_event_count[idx]) अणु
			occurred = 1;
			stdev->link_event_count[idx] = count;
		पूर्ण
	पूर्ण

	अगर (occurred)
		schedule_work(&stdev->link_event_work);
पूर्ण

अटल व्योम enable_link_state_events(काष्ठा चयनtec_dev *stdev)
अणु
	पूर्णांक idx;

	क्रम (idx = 0; idx < stdev->pff_csr_count; idx++) अणु
		ioग_लिखो32(SWITCHTEC_EVENT_CLEAR |
			  SWITCHTEC_EVENT_EN_IRQ,
			  &stdev->mmio_pff_csr[idx].link_state_hdr);
	पूर्ण
पूर्ण

अटल व्योम enable_dma_mrpc(काष्ठा चयनtec_dev *stdev)
अणु
	ग_लिखोq(stdev->dma_mrpc_dma_addr, &stdev->mmio_mrpc->dma_addr);
	flush_wc_buf(stdev);
	ioग_लिखो32(SWITCHTEC_DMA_MRPC_EN, &stdev->mmio_mrpc->dma_en);
पूर्ण

अटल व्योम stdev_release(काष्ठा device *dev)
अणु
	काष्ठा चयनtec_dev *stdev = to_stdev(dev);

	अगर (stdev->dma_mrpc) अणु
		ioग_लिखो32(0, &stdev->mmio_mrpc->dma_en);
		flush_wc_buf(stdev);
		ग_लिखोq(0, &stdev->mmio_mrpc->dma_addr);
		dma_मुक्त_coherent(&stdev->pdev->dev, माप(*stdev->dma_mrpc),
				stdev->dma_mrpc, stdev->dma_mrpc_dma_addr);
	पूर्ण
	kमुक्त(stdev);
पूर्ण

अटल व्योम stdev_समाप्त(काष्ठा चयनtec_dev *stdev)
अणु
	काष्ठा चयनtec_user *stuser, *पंचांगpuser;

	pci_clear_master(stdev->pdev);

	cancel_delayed_work_sync(&stdev->mrpc_समयout);

	/* Mark the hardware as unavailable and complete all completions */
	mutex_lock(&stdev->mrpc_mutex);
	stdev->alive = false;

	/* Wake up and समाप्त any users रुकोing on an MRPC request */
	list_क्रम_each_entry_safe(stuser, पंचांगpuser, &stdev->mrpc_queue, list) अणु
		stuser->cmd_करोne = true;
		wake_up_पूर्णांकerruptible(&stuser->cmd_comp);
		list_del_init(&stuser->list);
		stuser_put(stuser);
	पूर्ण

	mutex_unlock(&stdev->mrpc_mutex);

	/* Wake up any users रुकोing on event_wq */
	wake_up_पूर्णांकerruptible(&stdev->event_wq);
पूर्ण

अटल काष्ठा चयनtec_dev *stdev_create(काष्ठा pci_dev *pdev)
अणु
	काष्ठा चयनtec_dev *stdev;
	पूर्णांक minor;
	काष्ठा device *dev;
	काष्ठा cdev *cdev;
	पूर्णांक rc;

	stdev = kzalloc_node(माप(*stdev), GFP_KERNEL,
			     dev_to_node(&pdev->dev));
	अगर (!stdev)
		वापस ERR_PTR(-ENOMEM);

	stdev->alive = true;
	stdev->pdev = pdev;
	INIT_LIST_HEAD(&stdev->mrpc_queue);
	mutex_init(&stdev->mrpc_mutex);
	stdev->mrpc_busy = 0;
	INIT_WORK(&stdev->mrpc_work, mrpc_event_work);
	INIT_DELAYED_WORK(&stdev->mrpc_समयout, mrpc_समयout_work);
	INIT_WORK(&stdev->link_event_work, link_event_work);
	init_रुकोqueue_head(&stdev->event_wq);
	atomic_set(&stdev->event_cnt, 0);

	dev = &stdev->dev;
	device_initialize(dev);
	dev->class = चयनtec_class;
	dev->parent = &pdev->dev;
	dev->groups = चयनtec_device_groups;
	dev->release = stdev_release;

	minor = ida_simple_get(&चयनtec_minor_ida, 0, 0,
			       GFP_KERNEL);
	अगर (minor < 0) अणु
		rc = minor;
		जाओ err_put;
	पूर्ण

	dev->devt = MKDEV(MAJOR(चयनtec_devt), minor);
	dev_set_name(dev, "switchtec%d", minor);

	cdev = &stdev->cdev;
	cdev_init(cdev, &चयनtec_fops);
	cdev->owner = THIS_MODULE;

	वापस stdev;

err_put:
	put_device(&stdev->dev);
	वापस ERR_PTR(rc);
पूर्ण

अटल पूर्णांक mask_event(काष्ठा चयनtec_dev *stdev, पूर्णांक eid, पूर्णांक idx)
अणु
	माप_प्रकार off = event_regs[eid].offset;
	u32 __iomem *hdr_reg;
	u32 hdr;

	hdr_reg = event_regs[eid].map_reg(stdev, off, idx);
	hdr = ioपढ़ो32(hdr_reg);

	अगर (!(hdr & SWITCHTEC_EVENT_OCCURRED && hdr & SWITCHTEC_EVENT_EN_IRQ))
		वापस 0;

	dev_dbg(&stdev->dev, "%s: %d %d %x\n", __func__, eid, idx, hdr);
	hdr &= ~(SWITCHTEC_EVENT_EN_IRQ | SWITCHTEC_EVENT_OCCURRED);
	ioग_लिखो32(hdr, hdr_reg);

	वापस 1;
पूर्ण

अटल पूर्णांक mask_all_events(काष्ठा चयनtec_dev *stdev, पूर्णांक eid)
अणु
	पूर्णांक idx;
	पूर्णांक count = 0;

	अगर (event_regs[eid].map_reg == part_ev_reg) अणु
		क्रम (idx = 0; idx < stdev->partition_count; idx++)
			count += mask_event(stdev, eid, idx);
	पूर्ण अन्यथा अगर (event_regs[eid].map_reg == pff_ev_reg) अणु
		क्रम (idx = 0; idx < stdev->pff_csr_count; idx++) अणु
			अगर (!stdev->pff_local[idx])
				जारी;

			count += mask_event(stdev, eid, idx);
		पूर्ण
	पूर्ण अन्यथा अणु
		count += mask_event(stdev, eid, 0);
	पूर्ण

	वापस count;
पूर्ण

अटल irqवापस_t चयनtec_event_isr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा चयनtec_dev *stdev = dev;
	u32 reg;
	irqवापस_t ret = IRQ_NONE;
	पूर्णांक eid, event_count = 0;

	reg = ioपढ़ो32(&stdev->mmio_part_cfg->mrpc_comp_hdr);
	अगर (reg & SWITCHTEC_EVENT_OCCURRED) अणु
		dev_dbg(&stdev->dev, "%s: mrpc comp\n", __func__);
		ret = IRQ_HANDLED;
		schedule_work(&stdev->mrpc_work);
		ioग_लिखो32(reg, &stdev->mmio_part_cfg->mrpc_comp_hdr);
	पूर्ण

	check_link_state_events(stdev);

	क्रम (eid = 0; eid < SWITCHTEC_IOCTL_MAX_EVENTS; eid++) अणु
		अगर (eid == SWITCHTEC_IOCTL_EVENT_LINK_STATE ||
		    eid == SWITCHTEC_IOCTL_EVENT_MRPC_COMP)
			जारी;

		event_count += mask_all_events(stdev, eid);
	पूर्ण

	अगर (event_count) अणु
		atomic_inc(&stdev->event_cnt);
		wake_up_पूर्णांकerruptible(&stdev->event_wq);
		dev_dbg(&stdev->dev, "%s: %d events\n", __func__,
			event_count);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण


अटल irqवापस_t चयनtec_dma_mrpc_isr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा चयनtec_dev *stdev = dev;
	irqवापस_t ret = IRQ_NONE;

	ioग_लिखो32(SWITCHTEC_EVENT_CLEAR |
		  SWITCHTEC_EVENT_EN_IRQ,
		  &stdev->mmio_part_cfg->mrpc_comp_hdr);
	schedule_work(&stdev->mrpc_work);

	ret = IRQ_HANDLED;
	वापस ret;
पूर्ण

अटल पूर्णांक चयनtec_init_isr(काष्ठा चयनtec_dev *stdev)
अणु
	पूर्णांक nvecs;
	पूर्णांक event_irq;
	पूर्णांक dma_mrpc_irq;
	पूर्णांक rc;

	अगर (nirqs < 4)
		nirqs = 4;

	nvecs = pci_alloc_irq_vectors(stdev->pdev, 1, nirqs,
				      PCI_IRQ_MSIX | PCI_IRQ_MSI |
				      PCI_IRQ_VIRTUAL);
	अगर (nvecs < 0)
		वापस nvecs;

	event_irq = ioपढ़ो16(&stdev->mmio_part_cfg->vep_vector_number);
	अगर (event_irq < 0 || event_irq >= nvecs)
		वापस -EFAULT;

	event_irq = pci_irq_vector(stdev->pdev, event_irq);
	अगर (event_irq < 0)
		वापस event_irq;

	rc = devm_request_irq(&stdev->pdev->dev, event_irq,
				चयनtec_event_isr, 0,
				KBUILD_MODNAME, stdev);

	अगर (rc)
		वापस rc;

	अगर (!stdev->dma_mrpc)
		वापस rc;

	dma_mrpc_irq = ioपढ़ो32(&stdev->mmio_mrpc->dma_vector);
	अगर (dma_mrpc_irq < 0 || dma_mrpc_irq >= nvecs)
		वापस -EFAULT;

	dma_mrpc_irq  = pci_irq_vector(stdev->pdev, dma_mrpc_irq);
	अगर (dma_mrpc_irq < 0)
		वापस dma_mrpc_irq;

	rc = devm_request_irq(&stdev->pdev->dev, dma_mrpc_irq,
				चयनtec_dma_mrpc_isr, 0,
				KBUILD_MODNAME, stdev);

	वापस rc;
पूर्ण

अटल व्योम init_pff(काष्ठा चयनtec_dev *stdev)
अणु
	पूर्णांक i;
	u32 reg;
	काष्ठा part_cfg_regs __iomem *pcfg = stdev->mmio_part_cfg;

	क्रम (i = 0; i < SWITCHTEC_MAX_PFF_CSR; i++) अणु
		reg = ioपढ़ो16(&stdev->mmio_pff_csr[i].venकरोr_id);
		अगर (reg != PCI_VENDOR_ID_MICROSEMI)
			अवरोध;
	पूर्ण

	stdev->pff_csr_count = i;

	reg = ioपढ़ो32(&pcfg->usp_pff_inst_id);
	अगर (reg < stdev->pff_csr_count)
		stdev->pff_local[reg] = 1;

	reg = ioपढ़ो32(&pcfg->vep_pff_inst_id);
	अगर (reg < stdev->pff_csr_count)
		stdev->pff_local[reg] = 1;

	क्रम (i = 0; i < ARRAY_SIZE(pcfg->dsp_pff_inst_id); i++) अणु
		reg = ioपढ़ो32(&pcfg->dsp_pff_inst_id[i]);
		अगर (reg < stdev->pff_csr_count)
			stdev->pff_local[reg] = 1;
	पूर्ण
पूर्ण

अटल पूर्णांक चयनtec_init_pci(काष्ठा चयनtec_dev *stdev,
			      काष्ठा pci_dev *pdev)
अणु
	पूर्णांक rc;
	व्योम __iomem *map;
	अचिन्हित दीर्घ res_start, res_len;
	u32 __iomem *part_id;

	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (rc)
		वापस rc;

	pci_set_master(pdev);

	res_start = pci_resource_start(pdev, 0);
	res_len = pci_resource_len(pdev, 0);

	अगर (!devm_request_mem_region(&pdev->dev, res_start,
				     res_len, KBUILD_MODNAME))
		वापस -EBUSY;

	stdev->mmio_mrpc = devm_ioremap_wc(&pdev->dev, res_start,
					   SWITCHTEC_GAS_TOP_CFG_OFFSET);
	अगर (!stdev->mmio_mrpc)
		वापस -ENOMEM;

	map = devm_ioremap(&pdev->dev,
			   res_start + SWITCHTEC_GAS_TOP_CFG_OFFSET,
			   res_len - SWITCHTEC_GAS_TOP_CFG_OFFSET);
	अगर (!map)
		वापस -ENOMEM;

	stdev->mmio = map - SWITCHTEC_GAS_TOP_CFG_OFFSET;
	stdev->mmio_sw_event = stdev->mmio + SWITCHTEC_GAS_SW_EVENT_OFFSET;
	stdev->mmio_sys_info = stdev->mmio + SWITCHTEC_GAS_SYS_INFO_OFFSET;
	stdev->mmio_flash_info = stdev->mmio + SWITCHTEC_GAS_FLASH_INFO_OFFSET;
	stdev->mmio_ntb = stdev->mmio + SWITCHTEC_GAS_NTB_OFFSET;

	अगर (stdev->gen == SWITCHTEC_GEN3)
		part_id = &stdev->mmio_sys_info->gen3.partition_id;
	अन्यथा अगर (stdev->gen == SWITCHTEC_GEN4)
		part_id = &stdev->mmio_sys_info->gen4.partition_id;
	अन्यथा
		वापस -ENOTSUPP;

	stdev->partition = ioपढ़ो8(part_id);
	stdev->partition_count = ioपढ़ो8(&stdev->mmio_ntb->partition_count);
	stdev->mmio_part_cfg_all = stdev->mmio + SWITCHTEC_GAS_PART_CFG_OFFSET;
	stdev->mmio_part_cfg = &stdev->mmio_part_cfg_all[stdev->partition];
	stdev->mmio_pff_csr = stdev->mmio + SWITCHTEC_GAS_PFF_CSR_OFFSET;

	अगर (stdev->partition_count < 1)
		stdev->partition_count = 1;

	init_pff(stdev);

	pci_set_drvdata(pdev, stdev);

	अगर (!use_dma_mrpc)
		वापस 0;

	अगर (ioपढ़ो32(&stdev->mmio_mrpc->dma_ver) == 0)
		वापस 0;

	stdev->dma_mrpc = dma_alloc_coherent(&stdev->pdev->dev,
					     माप(*stdev->dma_mrpc),
					     &stdev->dma_mrpc_dma_addr,
					     GFP_KERNEL);
	अगर (stdev->dma_mrpc == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक चयनtec_pci_probe(काष्ठा pci_dev *pdev,
			       स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा चयनtec_dev *stdev;
	पूर्णांक rc;

	अगर (pdev->class == (PCI_CLASS_BRIDGE_OTHER << 8))
		request_module_noरुको("ntb_hw_switchtec");

	stdev = stdev_create(pdev);
	अगर (IS_ERR(stdev))
		वापस PTR_ERR(stdev);

	stdev->gen = id->driver_data;

	rc = चयनtec_init_pci(stdev, pdev);
	अगर (rc)
		जाओ err_put;

	rc = चयनtec_init_isr(stdev);
	अगर (rc) अणु
		dev_err(&stdev->dev, "failed to init isr.\n");
		जाओ err_put;
	पूर्ण

	ioग_लिखो32(SWITCHTEC_EVENT_CLEAR |
		  SWITCHTEC_EVENT_EN_IRQ,
		  &stdev->mmio_part_cfg->mrpc_comp_hdr);
	enable_link_state_events(stdev);

	अगर (stdev->dma_mrpc)
		enable_dma_mrpc(stdev);

	rc = cdev_device_add(&stdev->cdev, &stdev->dev);
	अगर (rc)
		जाओ err_devadd;

	dev_info(&stdev->dev, "Management device registered.\n");

	वापस 0;

err_devadd:
	stdev_समाप्त(stdev);
err_put:
	ida_simple_हटाओ(&चयनtec_minor_ida, MINOR(stdev->dev.devt));
	put_device(&stdev->dev);
	वापस rc;
पूर्ण

अटल व्योम चयनtec_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा चयनtec_dev *stdev = pci_get_drvdata(pdev);

	pci_set_drvdata(pdev, शून्य);

	cdev_device_del(&stdev->cdev, &stdev->dev);
	ida_simple_हटाओ(&चयनtec_minor_ida, MINOR(stdev->dev.devt));
	dev_info(&stdev->dev, "unregistered.\n");
	stdev_समाप्त(stdev);
	put_device(&stdev->dev);
पूर्ण

#घोषणा SWITCHTEC_PCI_DEVICE(device_id, gen) \
	अणु \
		.venकरोr     = PCI_VENDOR_ID_MICROSEMI, \
		.device     = device_id, \
		.subvenकरोr  = PCI_ANY_ID, \
		.subdevice  = PCI_ANY_ID, \
		.class      = (PCI_CLASS_MEMORY_OTHER << 8), \
		.class_mask = 0xFFFFFFFF, \
		.driver_data = gen, \
	पूर्ण, \
	अणु \
		.venकरोr     = PCI_VENDOR_ID_MICROSEMI, \
		.device     = device_id, \
		.subvenकरोr  = PCI_ANY_ID, \
		.subdevice  = PCI_ANY_ID, \
		.class      = (PCI_CLASS_BRIDGE_OTHER << 8), \
		.class_mask = 0xFFFFFFFF, \
		.driver_data = gen, \
	पूर्ण

अटल स्थिर काष्ठा pci_device_id चयनtec_pci_tbl[] = अणु
	SWITCHTEC_PCI_DEVICE(0x8531, SWITCHTEC_GEN3),  //PFX 24xG3
	SWITCHTEC_PCI_DEVICE(0x8532, SWITCHTEC_GEN3),  //PFX 32xG3
	SWITCHTEC_PCI_DEVICE(0x8533, SWITCHTEC_GEN3),  //PFX 48xG3
	SWITCHTEC_PCI_DEVICE(0x8534, SWITCHTEC_GEN3),  //PFX 64xG3
	SWITCHTEC_PCI_DEVICE(0x8535, SWITCHTEC_GEN3),  //PFX 80xG3
	SWITCHTEC_PCI_DEVICE(0x8536, SWITCHTEC_GEN3),  //PFX 96xG3
	SWITCHTEC_PCI_DEVICE(0x8541, SWITCHTEC_GEN3),  //PSX 24xG3
	SWITCHTEC_PCI_DEVICE(0x8542, SWITCHTEC_GEN3),  //PSX 32xG3
	SWITCHTEC_PCI_DEVICE(0x8543, SWITCHTEC_GEN3),  //PSX 48xG3
	SWITCHTEC_PCI_DEVICE(0x8544, SWITCHTEC_GEN3),  //PSX 64xG3
	SWITCHTEC_PCI_DEVICE(0x8545, SWITCHTEC_GEN3),  //PSX 80xG3
	SWITCHTEC_PCI_DEVICE(0x8546, SWITCHTEC_GEN3),  //PSX 96xG3
	SWITCHTEC_PCI_DEVICE(0x8551, SWITCHTEC_GEN3),  //PAX 24XG3
	SWITCHTEC_PCI_DEVICE(0x8552, SWITCHTEC_GEN3),  //PAX 32XG3
	SWITCHTEC_PCI_DEVICE(0x8553, SWITCHTEC_GEN3),  //PAX 48XG3
	SWITCHTEC_PCI_DEVICE(0x8554, SWITCHTEC_GEN3),  //PAX 64XG3
	SWITCHTEC_PCI_DEVICE(0x8555, SWITCHTEC_GEN3),  //PAX 80XG3
	SWITCHTEC_PCI_DEVICE(0x8556, SWITCHTEC_GEN3),  //PAX 96XG3
	SWITCHTEC_PCI_DEVICE(0x8561, SWITCHTEC_GEN3),  //PFXL 24XG3
	SWITCHTEC_PCI_DEVICE(0x8562, SWITCHTEC_GEN3),  //PFXL 32XG3
	SWITCHTEC_PCI_DEVICE(0x8563, SWITCHTEC_GEN3),  //PFXL 48XG3
	SWITCHTEC_PCI_DEVICE(0x8564, SWITCHTEC_GEN3),  //PFXL 64XG3
	SWITCHTEC_PCI_DEVICE(0x8565, SWITCHTEC_GEN3),  //PFXL 80XG3
	SWITCHTEC_PCI_DEVICE(0x8566, SWITCHTEC_GEN3),  //PFXL 96XG3
	SWITCHTEC_PCI_DEVICE(0x8571, SWITCHTEC_GEN3),  //PFXI 24XG3
	SWITCHTEC_PCI_DEVICE(0x8572, SWITCHTEC_GEN3),  //PFXI 32XG3
	SWITCHTEC_PCI_DEVICE(0x8573, SWITCHTEC_GEN3),  //PFXI 48XG3
	SWITCHTEC_PCI_DEVICE(0x8574, SWITCHTEC_GEN3),  //PFXI 64XG3
	SWITCHTEC_PCI_DEVICE(0x8575, SWITCHTEC_GEN3),  //PFXI 80XG3
	SWITCHTEC_PCI_DEVICE(0x8576, SWITCHTEC_GEN3),  //PFXI 96XG3
	SWITCHTEC_PCI_DEVICE(0x4000, SWITCHTEC_GEN4),  //PFX 100XG4
	SWITCHTEC_PCI_DEVICE(0x4084, SWITCHTEC_GEN4),  //PFX 84XG4
	SWITCHTEC_PCI_DEVICE(0x4068, SWITCHTEC_GEN4),  //PFX 68XG4
	SWITCHTEC_PCI_DEVICE(0x4052, SWITCHTEC_GEN4),  //PFX 52XG4
	SWITCHTEC_PCI_DEVICE(0x4036, SWITCHTEC_GEN4),  //PFX 36XG4
	SWITCHTEC_PCI_DEVICE(0x4028, SWITCHTEC_GEN4),  //PFX 28XG4
	SWITCHTEC_PCI_DEVICE(0x4100, SWITCHTEC_GEN4),  //PSX 100XG4
	SWITCHTEC_PCI_DEVICE(0x4184, SWITCHTEC_GEN4),  //PSX 84XG4
	SWITCHTEC_PCI_DEVICE(0x4168, SWITCHTEC_GEN4),  //PSX 68XG4
	SWITCHTEC_PCI_DEVICE(0x4152, SWITCHTEC_GEN4),  //PSX 52XG4
	SWITCHTEC_PCI_DEVICE(0x4136, SWITCHTEC_GEN4),  //PSX 36XG4
	SWITCHTEC_PCI_DEVICE(0x4128, SWITCHTEC_GEN4),  //PSX 28XG4
	SWITCHTEC_PCI_DEVICE(0x4200, SWITCHTEC_GEN4),  //PAX 100XG4
	SWITCHTEC_PCI_DEVICE(0x4284, SWITCHTEC_GEN4),  //PAX 84XG4
	SWITCHTEC_PCI_DEVICE(0x4268, SWITCHTEC_GEN4),  //PAX 68XG4
	SWITCHTEC_PCI_DEVICE(0x4252, SWITCHTEC_GEN4),  //PAX 52XG4
	SWITCHTEC_PCI_DEVICE(0x4236, SWITCHTEC_GEN4),  //PAX 36XG4
	SWITCHTEC_PCI_DEVICE(0x4228, SWITCHTEC_GEN4),  //PAX 28XG4
	अणु0पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, चयनtec_pci_tbl);

अटल काष्ठा pci_driver चयनtec_pci_driver = अणु
	.name		= KBUILD_MODNAME,
	.id_table	= चयनtec_pci_tbl,
	.probe		= चयनtec_pci_probe,
	.हटाओ		= चयनtec_pci_हटाओ,
पूर्ण;

अटल पूर्णांक __init चयनtec_init(व्योम)
अणु
	पूर्णांक rc;

	rc = alloc_chrdev_region(&चयनtec_devt, 0, max_devices,
				 "switchtec");
	अगर (rc)
		वापस rc;

	चयनtec_class = class_create(THIS_MODULE, "switchtec");
	अगर (IS_ERR(चयनtec_class)) अणु
		rc = PTR_ERR(चयनtec_class);
		जाओ err_create_class;
	पूर्ण

	rc = pci_रेजिस्टर_driver(&चयनtec_pci_driver);
	अगर (rc)
		जाओ err_pci_रेजिस्टर;

	pr_info(KBUILD_MODNAME ": loaded.\n");

	वापस 0;

err_pci_रेजिस्टर:
	class_destroy(चयनtec_class);

err_create_class:
	unरेजिस्टर_chrdev_region(चयनtec_devt, max_devices);

	वापस rc;
पूर्ण
module_init(चयनtec_init);

अटल व्योम __निकास चयनtec_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&चयनtec_pci_driver);
	class_destroy(चयनtec_class);
	unरेजिस्टर_chrdev_region(चयनtec_devt, max_devices);
	ida_destroy(&चयनtec_minor_ida);

	pr_info(KBUILD_MODNAME ": unloaded.\n");
पूर्ण
module_निकास(चयनtec_निकास);
