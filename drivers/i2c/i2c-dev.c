<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    i2c-dev.c - i2c-bus driver, अक्षर device पूर्णांकerface

    Copyright (C) 1995-97 Simon G. Vogl
    Copyright (C) 1998-99 Froकरो Looijaard <froकरोl@dds.nl>
    Copyright (C) 2003 Greg Kroah-Harपंचांगan <greg@kroah.com>

*/

/* Note that this is a complete reग_लिखो of Simon Vogl's i2c-dev module.
   But I have used so much of his original code and ideas that it seems
   only fair to recognize him as co-author -- Froकरो */

/* The I2C_RDWR ioctl code is written by Kolja Waschk <waschk@telos.de> */

#समावेश <linux/cdev.h>
#समावेश <linux/compat.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/i2c-dev.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

/*
 * An i2c_dev represents an i2c_adapter ... an I2C or SMBus master, not a
 * slave (i2c_client) with which messages will be exchanged.  It's coupled
 * with a अक्षरacter special file which is accessed by user mode drivers.
 *
 * The list of i2c_dev काष्ठाures is parallel to the i2c_adapter lists
 * मुख्यtained by the driver model, and is updated using bus notअगरications.
 */
काष्ठा i2c_dev अणु
	काष्ठा list_head list;
	काष्ठा i2c_adapter *adap;
	काष्ठा device dev;
	काष्ठा cdev cdev;
पूर्ण;

#घोषणा I2C_MINORS	(MINORMASK + 1)
अटल LIST_HEAD(i2c_dev_list);
अटल DEFINE_SPINLOCK(i2c_dev_list_lock);

अटल काष्ठा i2c_dev *i2c_dev_get_by_minor(अचिन्हित index)
अणु
	काष्ठा i2c_dev *i2c_dev;

	spin_lock(&i2c_dev_list_lock);
	list_क्रम_each_entry(i2c_dev, &i2c_dev_list, list) अणु
		अगर (i2c_dev->adap->nr == index)
			जाओ found;
	पूर्ण
	i2c_dev = शून्य;
found:
	spin_unlock(&i2c_dev_list_lock);
	वापस i2c_dev;
पूर्ण

अटल काष्ठा i2c_dev *get_मुक्त_i2c_dev(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा i2c_dev *i2c_dev;

	अगर (adap->nr >= I2C_MINORS) अणु
		prपूर्णांकk(KERN_ERR "i2c-dev: Out of device minors (%d)\n",
		       adap->nr);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	i2c_dev = kzalloc(माप(*i2c_dev), GFP_KERNEL);
	अगर (!i2c_dev)
		वापस ERR_PTR(-ENOMEM);
	i2c_dev->adap = adap;

	spin_lock(&i2c_dev_list_lock);
	list_add_tail(&i2c_dev->list, &i2c_dev_list);
	spin_unlock(&i2c_dev_list_lock);
	वापस i2c_dev;
पूर्ण

अटल व्योम put_i2c_dev(काष्ठा i2c_dev *i2c_dev, bool del_cdev)
अणु
	spin_lock(&i2c_dev_list_lock);
	list_del(&i2c_dev->list);
	spin_unlock(&i2c_dev_list_lock);
	अगर (del_cdev)
		cdev_device_del(&i2c_dev->cdev, &i2c_dev->dev);
	put_device(&i2c_dev->dev);
पूर्ण

अटल sमाप_प्रकार name_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_dev *i2c_dev = i2c_dev_get_by_minor(MINOR(dev->devt));

	अगर (!i2c_dev)
		वापस -ENODEV;
	वापस प्र_लिखो(buf, "%s\n", i2c_dev->adap->name);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल काष्ठा attribute *i2c_attrs[] = अणु
	&dev_attr_name.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(i2c);

/* ------------------------------------------------------------------------- */

/*
 * After खोलोing an instance of this अक्षरacter special file, a file
 * descriptor starts out associated only with an i2c_adapter (and bus).
 *
 * Using the I2C_RDWR ioctl(), you can then *immediately* issue i2c_msg
 * traffic to any devices on the bus used by that adapter.  That's because
 * the i2c_msg vectors embed all the addressing inक्रमmation they need, and
 * are submitted directly to an i2c_adapter.  However, SMBus-only adapters
 * करोn't support that पूर्णांकerface.
 *
 * To use पढ़ो()/ग_लिखो() प्रणाली calls on that file descriptor, or to use
 * SMBus पूर्णांकerfaces (and work with SMBus-only hosts!), you must first issue
 * an I2C_SLAVE (or I2C_SLAVE_FORCE) ioctl.  That configures an anonymous
 * (never रेजिस्टरed) i2c_client so it holds the addressing inक्रमmation
 * needed by those प्रणाली calls and by this SMBus पूर्णांकerface.
 */

अटल sमाप_प्रकार i2cdev_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
		loff_t *offset)
अणु
	अक्षर *पंचांगp;
	पूर्णांक ret;

	काष्ठा i2c_client *client = file->निजी_data;

	अगर (count > 8192)
		count = 8192;

	पंचांगp = kदो_स्मृति(count, GFP_KERNEL);
	अगर (पंचांगp == शून्य)
		वापस -ENOMEM;

	pr_debug("i2c-dev: i2c-%d reading %zu bytes.\n",
		iminor(file_inode(file)), count);

	ret = i2c_master_recv(client, पंचांगp, count);
	अगर (ret >= 0)
		ret = copy_to_user(buf, पंचांगp, count) ? -EFAULT : ret;
	kमुक्त(पंचांगp);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार i2cdev_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
		माप_प्रकार count, loff_t *offset)
अणु
	पूर्णांक ret;
	अक्षर *पंचांगp;
	काष्ठा i2c_client *client = file->निजी_data;

	अगर (count > 8192)
		count = 8192;

	पंचांगp = memdup_user(buf, count);
	अगर (IS_ERR(पंचांगp))
		वापस PTR_ERR(पंचांगp);

	pr_debug("i2c-dev: i2c-%d writing %zu bytes.\n",
		iminor(file_inode(file)), count);

	ret = i2c_master_send(client, पंचांगp, count);
	kमुक्त(पंचांगp);
	वापस ret;
पूर्ण

अटल पूर्णांक i2cdev_check(काष्ठा device *dev, व्योम *addrp)
अणु
	काष्ठा i2c_client *client = i2c_verअगरy_client(dev);

	अगर (!client || client->addr != *(अचिन्हित पूर्णांक *)addrp)
		वापस 0;

	वापस dev->driver ? -EBUSY : 0;
पूर्ण

/* walk up mux tree */
अटल पूर्णांक i2cdev_check_mux_parents(काष्ठा i2c_adapter *adapter, पूर्णांक addr)
अणु
	काष्ठा i2c_adapter *parent = i2c_parent_is_i2c_adapter(adapter);
	पूर्णांक result;

	result = device_क्रम_each_child(&adapter->dev, &addr, i2cdev_check);
	अगर (!result && parent)
		result = i2cdev_check_mux_parents(parent, addr);

	वापस result;
पूर्ण

/* recurse करोwn mux tree */
अटल पूर्णांक i2cdev_check_mux_children(काष्ठा device *dev, व्योम *addrp)
अणु
	पूर्णांक result;

	अगर (dev->type == &i2c_adapter_type)
		result = device_क्रम_each_child(dev, addrp,
						i2cdev_check_mux_children);
	अन्यथा
		result = i2cdev_check(dev, addrp);

	वापस result;
पूर्ण

/* This address checking function dअगरfers from the one in i2c-core
   in that it considers an address with a रेजिस्टरed device, but no
   driver bound to it, as NOT busy. */
अटल पूर्णांक i2cdev_check_addr(काष्ठा i2c_adapter *adapter, अचिन्हित पूर्णांक addr)
अणु
	काष्ठा i2c_adapter *parent = i2c_parent_is_i2c_adapter(adapter);
	पूर्णांक result = 0;

	अगर (parent)
		result = i2cdev_check_mux_parents(parent, addr);

	अगर (!result)
		result = device_क्रम_each_child(&adapter->dev, &addr,
						i2cdev_check_mux_children);

	वापस result;
पूर्ण

अटल noअंतरभूत पूर्णांक i2cdev_ioctl_rdwr(काष्ठा i2c_client *client,
		अचिन्हित nmsgs, काष्ठा i2c_msg *msgs)
अणु
	u8 __user **data_ptrs;
	पूर्णांक i, res;

	data_ptrs = kदो_स्मृति_array(nmsgs, माप(u8 __user *), GFP_KERNEL);
	अगर (data_ptrs == शून्य) अणु
		kमुक्त(msgs);
		वापस -ENOMEM;
	पूर्ण

	res = 0;
	क्रम (i = 0; i < nmsgs; i++) अणु
		/* Limit the size of the message to a sane amount */
		अगर (msgs[i].len > 8192) अणु
			res = -EINVAL;
			अवरोध;
		पूर्ण

		data_ptrs[i] = (u8 __user *)msgs[i].buf;
		msgs[i].buf = memdup_user(data_ptrs[i], msgs[i].len);
		अगर (IS_ERR(msgs[i].buf)) अणु
			res = PTR_ERR(msgs[i].buf);
			अवरोध;
		पूर्ण
		/* memdup_user allocates with GFP_KERNEL, so DMA is ok */
		msgs[i].flags |= I2C_M_DMA_SAFE;

		/*
		 * If the message length is received from the slave (similar
		 * to SMBus block पढ़ो), we must ensure that the buffer will
		 * be large enough to cope with a message length of
		 * I2C_SMBUS_BLOCK_MAX as this is the maximum underlying bus
		 * drivers allow. The first byte in the buffer must be
		 * pre-filled with the number of extra bytes, which must be
		 * at least one to hold the message length, but can be
		 * greater (क्रम example to account क्रम a checksum byte at
		 * the end of the message.)
		 */
		अगर (msgs[i].flags & I2C_M_RECV_LEN) अणु
			अगर (!(msgs[i].flags & I2C_M_RD) ||
			    msgs[i].len < 1 || msgs[i].buf[0] < 1 ||
			    msgs[i].len < msgs[i].buf[0] +
					     I2C_SMBUS_BLOCK_MAX) अणु
				i++;
				res = -EINVAL;
				अवरोध;
			पूर्ण

			msgs[i].len = msgs[i].buf[0];
		पूर्ण
	पूर्ण
	अगर (res < 0) अणु
		पूर्णांक j;
		क्रम (j = 0; j < i; ++j)
			kमुक्त(msgs[j].buf);
		kमुक्त(data_ptrs);
		kमुक्त(msgs);
		वापस res;
	पूर्ण

	res = i2c_transfer(client->adapter, msgs, nmsgs);
	जबतक (i-- > 0) अणु
		अगर (res >= 0 && (msgs[i].flags & I2C_M_RD)) अणु
			अगर (copy_to_user(data_ptrs[i], msgs[i].buf,
					 msgs[i].len))
				res = -EFAULT;
		पूर्ण
		kमुक्त(msgs[i].buf);
	पूर्ण
	kमुक्त(data_ptrs);
	kमुक्त(msgs);
	वापस res;
पूर्ण

अटल noअंतरभूत पूर्णांक i2cdev_ioctl_smbus(काष्ठा i2c_client *client,
		u8 पढ़ो_ग_लिखो, u8 command, u32 size,
		जोड़ i2c_smbus_data __user *data)
अणु
	जोड़ i2c_smbus_data temp = अणुपूर्ण;
	पूर्णांक datasize, res;

	अगर ((size != I2C_SMBUS_BYTE) &&
	    (size != I2C_SMBUS_QUICK) &&
	    (size != I2C_SMBUS_BYTE_DATA) &&
	    (size != I2C_SMBUS_WORD_DATA) &&
	    (size != I2C_SMBUS_PROC_CALL) &&
	    (size != I2C_SMBUS_BLOCK_DATA) &&
	    (size != I2C_SMBUS_I2C_BLOCK_BROKEN) &&
	    (size != I2C_SMBUS_I2C_BLOCK_DATA) &&
	    (size != I2C_SMBUS_BLOCK_PROC_CALL)) अणु
		dev_dbg(&client->adapter->dev,
			"size out of range (%x) in ioctl I2C_SMBUS.\n",
			size);
		वापस -EINVAL;
	पूर्ण
	/* Note that I2C_SMBUS_READ and I2C_SMBUS_WRITE are 0 and 1,
	   so the check is valid अगर size==I2C_SMBUS_QUICK too. */
	अगर ((पढ़ो_ग_लिखो != I2C_SMBUS_READ) &&
	    (पढ़ो_ग_लिखो != I2C_SMBUS_WRITE)) अणु
		dev_dbg(&client->adapter->dev,
			"read_write out of range (%x) in ioctl I2C_SMBUS.\n",
			पढ़ो_ग_लिखो);
		वापस -EINVAL;
	पूर्ण

	/* Note that command values are always valid! */

	अगर ((size == I2C_SMBUS_QUICK) ||
	    ((size == I2C_SMBUS_BYTE) &&
	    (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)))
		/* These are special: we करो not use data */
		वापस i2c_smbus_xfer(client->adapter, client->addr,
				      client->flags, पढ़ो_ग_लिखो,
				      command, size, शून्य);

	अगर (data == शून्य) अणु
		dev_dbg(&client->adapter->dev,
			"data is NULL pointer in ioctl I2C_SMBUS.\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((size == I2C_SMBUS_BYTE_DATA) ||
	    (size == I2C_SMBUS_BYTE))
		datasize = माप(data->byte);
	अन्यथा अगर ((size == I2C_SMBUS_WORD_DATA) ||
		 (size == I2C_SMBUS_PROC_CALL))
		datasize = माप(data->word);
	अन्यथा /* size == smbus block, i2c block, or block proc. call */
		datasize = माप(data->block);

	अगर ((size == I2C_SMBUS_PROC_CALL) ||
	    (size == I2C_SMBUS_BLOCK_PROC_CALL) ||
	    (size == I2C_SMBUS_I2C_BLOCK_DATA) ||
	    (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)) अणु
		अगर (copy_from_user(&temp, data, datasize))
			वापस -EFAULT;
	पूर्ण
	अगर (size == I2C_SMBUS_I2C_BLOCK_BROKEN) अणु
		/* Convert old I2C block commands to the new
		   convention. This preserves binary compatibility. */
		size = I2C_SMBUS_I2C_BLOCK_DATA;
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ)
			temp.block[0] = I2C_SMBUS_BLOCK_MAX;
	पूर्ण
	res = i2c_smbus_xfer(client->adapter, client->addr, client->flags,
	      पढ़ो_ग_लिखो, command, size, &temp);
	अगर (!res && ((size == I2C_SMBUS_PROC_CALL) ||
		     (size == I2C_SMBUS_BLOCK_PROC_CALL) ||
		     (पढ़ो_ग_लिखो == I2C_SMBUS_READ))) अणु
		अगर (copy_to_user(data, &temp, datasize))
			वापस -EFAULT;
	पूर्ण
	वापस res;
पूर्ण

अटल दीर्घ i2cdev_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा i2c_client *client = file->निजी_data;
	अचिन्हित दीर्घ funcs;

	dev_dbg(&client->adapter->dev, "ioctl, cmd=0x%02x, arg=0x%02lx\n",
		cmd, arg);

	चयन (cmd) अणु
	हाल I2C_SLAVE:
	हाल I2C_SLAVE_FORCE:
		अगर ((arg > 0x3ff) ||
		    (((client->flags & I2C_M_TEN) == 0) && arg > 0x7f))
			वापस -EINVAL;
		अगर (cmd == I2C_SLAVE && i2cdev_check_addr(client->adapter, arg))
			वापस -EBUSY;
		/* REVISIT: address could become busy later */
		client->addr = arg;
		वापस 0;
	हाल I2C_TENBIT:
		अगर (arg)
			client->flags |= I2C_M_TEN;
		अन्यथा
			client->flags &= ~I2C_M_TEN;
		वापस 0;
	हाल I2C_PEC:
		/*
		 * Setting the PEC flag here won't affect kernel drivers,
		 * which will be using the i2c_client node रेजिस्टरed with
		 * the driver model core.  Likewise, when that client has
		 * the PEC flag alपढ़ोy set, the i2c-dev driver won't see
		 * (or use) this setting.
		 */
		अगर (arg)
			client->flags |= I2C_CLIENT_PEC;
		अन्यथा
			client->flags &= ~I2C_CLIENT_PEC;
		वापस 0;
	हाल I2C_FUNCS:
		funcs = i2c_get_functionality(client->adapter);
		वापस put_user(funcs, (अचिन्हित दीर्घ __user *)arg);

	हाल I2C_RDWR: अणु
		काष्ठा i2c_rdwr_ioctl_data rdwr_arg;
		काष्ठा i2c_msg *rdwr_pa;

		अगर (copy_from_user(&rdwr_arg,
				   (काष्ठा i2c_rdwr_ioctl_data __user *)arg,
				   माप(rdwr_arg)))
			वापस -EFAULT;

		अगर (!rdwr_arg.msgs || rdwr_arg.nmsgs == 0)
			वापस -EINVAL;

		/*
		 * Put an arbitrary limit on the number of messages that can
		 * be sent at once
		 */
		अगर (rdwr_arg.nmsgs > I2C_RDWR_IOCTL_MAX_MSGS)
			वापस -EINVAL;

		rdwr_pa = memdup_user(rdwr_arg.msgs,
				      rdwr_arg.nmsgs * माप(काष्ठा i2c_msg));
		अगर (IS_ERR(rdwr_pa))
			वापस PTR_ERR(rdwr_pa);

		वापस i2cdev_ioctl_rdwr(client, rdwr_arg.nmsgs, rdwr_pa);
	पूर्ण

	हाल I2C_SMBUS: अणु
		काष्ठा i2c_smbus_ioctl_data data_arg;
		अगर (copy_from_user(&data_arg,
				   (काष्ठा i2c_smbus_ioctl_data __user *) arg,
				   माप(काष्ठा i2c_smbus_ioctl_data)))
			वापस -EFAULT;
		वापस i2cdev_ioctl_smbus(client, data_arg.पढ़ो_ग_लिखो,
					  data_arg.command,
					  data_arg.size,
					  data_arg.data);
	पूर्ण
	हाल I2C_RETRIES:
		अगर (arg > पूर्णांक_उच्च)
			वापस -EINVAL;

		client->adapter->retries = arg;
		अवरोध;
	हाल I2C_TIMEOUT:
		अगर (arg > पूर्णांक_उच्च)
			वापस -EINVAL;

		/* For historical reasons, user-space sets the समयout
		 * value in units of 10 ms.
		 */
		client->adapter->समयout = msecs_to_jअगरfies(arg * 10);
		अवरोध;
	शेष:
		/* NOTE:  वापसing a fault code here could cause trouble
		 * in buggy userspace code.  Some old kernel bugs वापसed
		 * zero in this हाल, and userspace code might accidentally
		 * have depended on that bug.
		 */
		वापस -ENOTTY;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT

काष्ठा i2c_smbus_ioctl_data32 अणु
	u8 पढ़ो_ग_लिखो;
	u8 command;
	u32 size;
	compat_caddr_t data; /* जोड़ i2c_smbus_data *data */
पूर्ण;

काष्ठा i2c_msg32 अणु
	u16 addr;
	u16 flags;
	u16 len;
	compat_caddr_t buf;
पूर्ण;

काष्ठा i2c_rdwr_ioctl_data32 अणु
	compat_caddr_t msgs; /* काष्ठा i2c_msg __user *msgs */
	u32 nmsgs;
पूर्ण;

अटल दीर्घ compat_i2cdev_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा i2c_client *client = file->निजी_data;
	अचिन्हित दीर्घ funcs;
	चयन (cmd) अणु
	हाल I2C_FUNCS:
		funcs = i2c_get_functionality(client->adapter);
		वापस put_user(funcs, (compat_uदीर्घ_t __user *)arg);
	हाल I2C_RDWR: अणु
		काष्ठा i2c_rdwr_ioctl_data32 rdwr_arg;
		काष्ठा i2c_msg32 *p;
		काष्ठा i2c_msg *rdwr_pa;
		पूर्णांक i;

		अगर (copy_from_user(&rdwr_arg,
				   (काष्ठा i2c_rdwr_ioctl_data32 __user *)arg,
				   माप(rdwr_arg)))
			वापस -EFAULT;

		अगर (rdwr_arg.nmsgs > I2C_RDWR_IOCTL_MAX_MSGS)
			वापस -EINVAL;

		rdwr_pa = kदो_स्मृति_array(rdwr_arg.nmsgs, माप(काष्ठा i2c_msg),
				      GFP_KERNEL);
		अगर (!rdwr_pa)
			वापस -ENOMEM;

		p = compat_ptr(rdwr_arg.msgs);
		क्रम (i = 0; i < rdwr_arg.nmsgs; i++) अणु
			काष्ठा i2c_msg32 umsg;
			अगर (copy_from_user(&umsg, p + i, माप(umsg))) अणु
				kमुक्त(rdwr_pa);
				वापस -EFAULT;
			पूर्ण
			rdwr_pa[i] = (काष्ठा i2c_msg) अणु
				.addr = umsg.addr,
				.flags = umsg.flags,
				.len = umsg.len,
				.buf = compat_ptr(umsg.buf)
			पूर्ण;
		पूर्ण

		वापस i2cdev_ioctl_rdwr(client, rdwr_arg.nmsgs, rdwr_pa);
	पूर्ण
	हाल I2C_SMBUS: अणु
		काष्ठा i2c_smbus_ioctl_data32	data32;
		अगर (copy_from_user(&data32,
				   (व्योम __user *) arg,
				   माप(data32)))
			वापस -EFAULT;
		वापस i2cdev_ioctl_smbus(client, data32.पढ़ो_ग_लिखो,
					  data32.command,
					  data32.size,
					  compat_ptr(data32.data));
	पूर्ण
	शेष:
		वापस i2cdev_ioctl(file, cmd, arg);
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा compat_i2cdev_ioctl शून्य
#पूर्ण_अगर

अटल पूर्णांक i2cdev_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक minor = iminor(inode);
	काष्ठा i2c_client *client;
	काष्ठा i2c_adapter *adap;

	adap = i2c_get_adapter(minor);
	अगर (!adap)
		वापस -ENODEV;

	/* This creates an anonymous i2c_client, which may later be
	 * poपूर्णांकed to some address using I2C_SLAVE or I2C_SLAVE_FORCE.
	 *
	 * This client is ** NEVER REGISTERED ** with the driver model
	 * or I2C core code!!  It just holds निजी copies of addressing
	 * inक्रमmation and maybe a PEC flag.
	 */
	client = kzalloc(माप(*client), GFP_KERNEL);
	अगर (!client) अणु
		i2c_put_adapter(adap);
		वापस -ENOMEM;
	पूर्ण
	snम_लिखो(client->name, I2C_NAME_SIZE, "i2c-dev %d", adap->nr);

	client->adapter = adap;
	file->निजी_data = client;

	वापस 0;
पूर्ण

अटल पूर्णांक i2cdev_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा i2c_client *client = file->निजी_data;

	i2c_put_adapter(client->adapter);
	kमुक्त(client);
	file->निजी_data = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations i2cdev_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= no_llseek,
	.पढ़ो		= i2cdev_पढ़ो,
	.ग_लिखो		= i2cdev_ग_लिखो,
	.unlocked_ioctl	= i2cdev_ioctl,
	.compat_ioctl	= compat_i2cdev_ioctl,
	.खोलो		= i2cdev_खोलो,
	.release	= i2cdev_release,
पूर्ण;

/* ------------------------------------------------------------------------- */

अटल काष्ठा class *i2c_dev_class;

अटल व्योम i2cdev_dev_release(काष्ठा device *dev)
अणु
	काष्ठा i2c_dev *i2c_dev;

	i2c_dev = container_of(dev, काष्ठा i2c_dev, dev);
	kमुक्त(i2c_dev);
पूर्ण

अटल पूर्णांक i2cdev_attach_adapter(काष्ठा device *dev, व्योम *dummy)
अणु
	काष्ठा i2c_adapter *adap;
	काष्ठा i2c_dev *i2c_dev;
	पूर्णांक res;

	अगर (dev->type != &i2c_adapter_type)
		वापस 0;
	adap = to_i2c_adapter(dev);

	i2c_dev = get_मुक्त_i2c_dev(adap);
	अगर (IS_ERR(i2c_dev))
		वापस PTR_ERR(i2c_dev);

	cdev_init(&i2c_dev->cdev, &i2cdev_fops);
	i2c_dev->cdev.owner = THIS_MODULE;

	device_initialize(&i2c_dev->dev);
	i2c_dev->dev.devt = MKDEV(I2C_MAJOR, adap->nr);
	i2c_dev->dev.class = i2c_dev_class;
	i2c_dev->dev.parent = &adap->dev;
	i2c_dev->dev.release = i2cdev_dev_release;
	dev_set_name(&i2c_dev->dev, "i2c-%d", adap->nr);

	res = cdev_device_add(&i2c_dev->cdev, &i2c_dev->dev);
	अगर (res) अणु
		put_i2c_dev(i2c_dev, false);
		वापस res;
	पूर्ण

	pr_debug("i2c-dev: adapter [%s] registered as minor %d\n",
		 adap->name, adap->nr);
	वापस 0;
पूर्ण

अटल पूर्णांक i2cdev_detach_adapter(काष्ठा device *dev, व्योम *dummy)
अणु
	काष्ठा i2c_adapter *adap;
	काष्ठा i2c_dev *i2c_dev;

	अगर (dev->type != &i2c_adapter_type)
		वापस 0;
	adap = to_i2c_adapter(dev);

	i2c_dev = i2c_dev_get_by_minor(adap->nr);
	अगर (!i2c_dev) /* attach_adapter must have failed */
		वापस 0;

	put_i2c_dev(i2c_dev, true);

	pr_debug("i2c-dev: adapter [%s] unregistered\n", adap->name);
	वापस 0;
पूर्ण

अटल पूर्णांक i2cdev_notअगरier_call(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
			 व्योम *data)
अणु
	काष्ठा device *dev = data;

	चयन (action) अणु
	हाल BUS_NOTIFY_ADD_DEVICE:
		वापस i2cdev_attach_adapter(dev, शून्य);
	हाल BUS_NOTIFY_DEL_DEVICE:
		वापस i2cdev_detach_adapter(dev, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block i2cdev_notअगरier = अणु
	.notअगरier_call = i2cdev_notअगरier_call,
पूर्ण;

/* ------------------------------------------------------------------------- */

/*
 * module load/unload record keeping
 */

अटल पूर्णांक __init i2c_dev_init(व्योम)
अणु
	पूर्णांक res;

	prपूर्णांकk(KERN_INFO "i2c /dev entries driver\n");

	res = रेजिस्टर_chrdev_region(MKDEV(I2C_MAJOR, 0), I2C_MINORS, "i2c");
	अगर (res)
		जाओ out;

	i2c_dev_class = class_create(THIS_MODULE, "i2c-dev");
	अगर (IS_ERR(i2c_dev_class)) अणु
		res = PTR_ERR(i2c_dev_class);
		जाओ out_unreg_chrdev;
	पूर्ण
	i2c_dev_class->dev_groups = i2c_groups;

	/* Keep track of adapters which will be added or हटाओd later */
	res = bus_रेजिस्टर_notअगरier(&i2c_bus_type, &i2cdev_notअगरier);
	अगर (res)
		जाओ out_unreg_class;

	/* Bind to alपढ़ोy existing adapters right away */
	i2c_क्रम_each_dev(शून्य, i2cdev_attach_adapter);

	वापस 0;

out_unreg_class:
	class_destroy(i2c_dev_class);
out_unreg_chrdev:
	unरेजिस्टर_chrdev_region(MKDEV(I2C_MAJOR, 0), I2C_MINORS);
out:
	prपूर्णांकk(KERN_ERR "%s: Driver Initialisation failed\n", __खाता__);
	वापस res;
पूर्ण

अटल व्योम __निकास i2c_dev_निकास(व्योम)
अणु
	bus_unरेजिस्टर_notअगरier(&i2c_bus_type, &i2cdev_notअगरier);
	i2c_क्रम_each_dev(शून्य, i2cdev_detach_adapter);
	class_destroy(i2c_dev_class);
	unरेजिस्टर_chrdev_region(MKDEV(I2C_MAJOR, 0), I2C_MINORS);
पूर्ण

MODULE_AUTHOR("Frodo Looijaard <frodol@dds.nl>");
MODULE_AUTHOR("Simon G. Vogl <simon@tk.uni-linz.ac.at>");
MODULE_DESCRIPTION("I2C /dev entries driver");
MODULE_LICENSE("GPL");

module_init(i2c_dev_init);
module_निकास(i2c_dev_निकास);
