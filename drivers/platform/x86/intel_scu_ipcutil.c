<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the Intel SCU IPC mechanism
 *
 * (C) Copyright 2008-2010 Intel Corporation
 * Author: Sreedhara DS (sreedhara.ds@पूर्णांकel.com)
 *
 * This driver provides IOCTL पूर्णांकerfaces to call Intel SCU IPC driver API.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/पूर्णांकel_scu_ipc.h>

अटल पूर्णांक major;

काष्ठा पूर्णांकel_scu_ipc_dev *scu;
अटल DEFINE_MUTEX(scu_lock);

/* IOCTL commands */
#घोषणा	INTE_SCU_IPC_REGISTER_READ	0
#घोषणा INTE_SCU_IPC_REGISTER_WRITE	1
#घोषणा INTE_SCU_IPC_REGISTER_UPDATE	2

काष्ठा scu_ipc_data अणु
	u32     count;  /* No. of रेजिस्टरs */
	u16     addr[5]; /* Register addresses */
	u8      data[5]; /* Register data */
	u8      mask; /* Valid क्रम पढ़ो-modअगरy-ग_लिखो */
पूर्ण;

/**
 *	scu_reg_access		-	implement रेजिस्टर access ioctls
 *	@cmd: command we are करोing (पढ़ो/ग_लिखो/update)
 *	@data: kernel copy of ioctl data
 *
 *	Allow the user to perक्रमm रेजिस्टर accesses on the SCU via the
 *	kernel पूर्णांकerface
 */

अटल पूर्णांक scu_reg_access(u32 cmd, काष्ठा scu_ipc_data  *data)
अणु
	अचिन्हित पूर्णांक count = data->count;

	अगर (count == 0 || count == 3 || count > 4)
		वापस -EINVAL;

	चयन (cmd) अणु
	हाल INTE_SCU_IPC_REGISTER_READ:
		वापस पूर्णांकel_scu_ipc_dev_पढ़ोv(scu, data->addr, data->data, count);
	हाल INTE_SCU_IPC_REGISTER_WRITE:
		वापस पूर्णांकel_scu_ipc_dev_ग_लिखोv(scu, data->addr, data->data, count);
	हाल INTE_SCU_IPC_REGISTER_UPDATE:
		वापस पूर्णांकel_scu_ipc_dev_update(scu, data->addr[0], data->data[0],
						data->mask);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

/**
 *	scu_ipc_ioctl		-	control ioctls क्रम the SCU
 *	@fp: file handle of the SCU device
 *	@cmd: ioctl coce
 *	@arg: poपूर्णांकer to user passed काष्ठाure
 *
 *	Support the I/O and firmware flashing पूर्णांकerfaces of the SCU
 */
अटल दीर्घ scu_ipc_ioctl(काष्ठा file *fp, अचिन्हित पूर्णांक cmd,
							अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;
	काष्ठा scu_ipc_data  data;
	व्योम __user *argp = (व्योम __user *)arg;

	अगर (!capable(CAP_SYS_RAWIO))
		वापस -EPERM;

	अगर (copy_from_user(&data, argp, माप(काष्ठा scu_ipc_data)))
		वापस -EFAULT;
	ret = scu_reg_access(cmd, &data);
	अगर (ret < 0)
		वापस ret;
	अगर (copy_to_user(argp, &data, माप(काष्ठा scu_ipc_data)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक scu_ipc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret = 0;

	/* Only single खोलो at the समय */
	mutex_lock(&scu_lock);
	अगर (scu) अणु
		ret = -EBUSY;
		जाओ unlock;
	पूर्ण

	scu = पूर्णांकel_scu_ipc_dev_get();
	अगर (!scu)
		ret = -ENODEV;

unlock:
	mutex_unlock(&scu_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक scu_ipc_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	mutex_lock(&scu_lock);
	पूर्णांकel_scu_ipc_dev_put(scu);
	scu = शून्य;
	mutex_unlock(&scu_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations scu_ipc_fops = अणु
	.unlocked_ioctl = scu_ipc_ioctl,
	.खोलो = scu_ipc_खोलो,
	.release = scu_ipc_release,
पूर्ण;

अटल पूर्णांक __init ipc_module_init(व्योम)
अणु
	major = रेजिस्टर_chrdev(0, "intel_mid_scu", &scu_ipc_fops);
	अगर (major < 0)
		वापस major;

	वापस 0;
पूर्ण

अटल व्योम __निकास ipc_module_निकास(व्योम)
अणु
	unरेजिस्टर_chrdev(major, "intel_mid_scu");
पूर्ण

module_init(ipc_module_init);
module_निकास(ipc_module_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Utility driver for intel scu ipc");
MODULE_AUTHOR("Sreedhara <sreedhara.ds@intel.com>");
