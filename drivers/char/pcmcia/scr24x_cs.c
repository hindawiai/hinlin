<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SCR24x PCMCIA Smart Card Reader Driver
 *
 * Copyright (C) 2005-2006 TL Sudheendran
 * Copyright (C) 2016 Lubomir Rपूर्णांकel
 *
 * Derived from "scr24x_v4.2.6_Release.tar.gz" driver by TL Sudheendran.
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/cdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/पन.स>
#समावेश <linux/uaccess.h>

#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>

#घोषणा CCID_HEADER_SIZE	10
#घोषणा CCID_LENGTH_OFFSET	1
#घोषणा CCID_MAX_LEN		271

#घोषणा SCR24X_DATA(n)		(1 + n)
#घोषणा SCR24X_CMD_STATUS	7
#घोषणा CMD_START		0x40
#घोषणा CMD_WRITE_BYTE		0x41
#घोषणा CMD_READ_BYTE		0x42
#घोषणा STATUS_BUSY		0x80

काष्ठा scr24x_dev अणु
	काष्ठा device *dev;
	काष्ठा cdev c_dev;
	अचिन्हित अक्षर buf[CCID_MAX_LEN];
	पूर्णांक devno;
	काष्ठा mutex lock;
	काष्ठा kref refcnt;
	u8 __iomem *regs;
पूर्ण;

#घोषणा SCR24X_DEVS 8
अटल DECLARE_BITMAP(scr24x_minors, SCR24X_DEVS);

अटल काष्ठा class *scr24x_class;
अटल dev_t scr24x_devt;

अटल व्योम scr24x_delete(काष्ठा kref *kref)
अणु
	काष्ठा scr24x_dev *dev = container_of(kref, काष्ठा scr24x_dev,
								refcnt);

	kमुक्त(dev);
पूर्ण

अटल पूर्णांक scr24x_रुको_पढ़ोy(काष्ठा scr24x_dev *dev)
अणु
	u_अक्षर status;
	पूर्णांक समयout = 100;

	करो अणु
		status = ioपढ़ो8(dev->regs + SCR24X_CMD_STATUS);
		अगर (!(status & STATUS_BUSY))
			वापस 0;

		msleep(20);
	पूर्ण जबतक (--समयout);

	वापस -EIO;
पूर्ण

अटल पूर्णांक scr24x_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा scr24x_dev *dev = container_of(inode->i_cdev,
				काष्ठा scr24x_dev, c_dev);

	kref_get(&dev->refcnt);
	filp->निजी_data = dev;

	वापस stream_खोलो(inode, filp);
पूर्ण

अटल पूर्णांक scr24x_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा scr24x_dev *dev = filp->निजी_data;

	/* We must not take the dev->lock here as scr24x_delete()
	 * might be called to हटाओ the dev काष्ठाure altogether.
	 * We करोn't need the lock anyway, since after the reference
	 * acquired in probe() is released in हटाओ() the chrdev
	 * is alपढ़ोy unरेजिस्टरed and noone can possibly acquire
	 * a reference via खोलो() anymore. */
	kref_put(&dev->refcnt, scr24x_delete);
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_chunk(काष्ठा scr24x_dev *dev, माप_प्रकार offset, माप_प्रकार limit)
अणु
	माप_प्रकार i, y;
	पूर्णांक ret;

	क्रम (i = offset; i < limit; i += 5) अणु
		ioग_लिखो8(CMD_READ_BYTE, dev->regs + SCR24X_CMD_STATUS);
		ret = scr24x_रुको_पढ़ोy(dev);
		अगर (ret < 0)
			वापस ret;

		क्रम (y = 0; y < 5 && i + y < limit; y++)
			dev->buf[i + y] = ioपढ़ो8(dev->regs + SCR24X_DATA(y));
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार scr24x_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count,
								loff_t *ppos)
अणु
	काष्ठा scr24x_dev *dev = filp->निजी_data;
	पूर्णांक ret;
	पूर्णांक len;

	अगर (count < CCID_HEADER_SIZE)
		वापस -EINVAL;

	अगर (mutex_lock_पूर्णांकerruptible(&dev->lock))
		वापस -ERESTARTSYS;

	अगर (!dev->dev) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	ret = scr24x_रुको_पढ़ोy(dev);
	अगर (ret < 0)
		जाओ out;
	len = CCID_HEADER_SIZE;
	ret = पढ़ो_chunk(dev, 0, len);
	अगर (ret < 0)
		जाओ out;

	len += le32_to_cpu(*(__le32 *)(&dev->buf[CCID_LENGTH_OFFSET]));
	अगर (len > माप(dev->buf)) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण
	ret = पढ़ो_chunk(dev, CCID_HEADER_SIZE, len);
	अगर (ret < 0)
		जाओ out;

	अगर (len < count)
		count = len;

	अगर (copy_to_user(buf, dev->buf, count)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	ret = count;
out:
	mutex_unlock(&dev->lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार scr24x_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा scr24x_dev *dev = filp->निजी_data;
	माप_प्रकार i, y;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&dev->lock))
		वापस -ERESTARTSYS;

	अगर (!dev->dev) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (count > माप(dev->buf)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (copy_from_user(dev->buf, buf, count)) अणु
		ret = -EFAULT;
		जाओ out;
	पूर्ण

	ret = scr24x_रुको_पढ़ोy(dev);
	अगर (ret < 0)
		जाओ out;

	ioग_लिखो8(CMD_START, dev->regs + SCR24X_CMD_STATUS);
	ret = scr24x_रुको_पढ़ोy(dev);
	अगर (ret < 0)
		जाओ out;

	क्रम (i = 0; i < count; i += 5) अणु
		क्रम (y = 0; y < 5 && i + y < count; y++)
			ioग_लिखो8(dev->buf[i + y], dev->regs + SCR24X_DATA(y));

		ioग_लिखो8(CMD_WRITE_BYTE, dev->regs + SCR24X_CMD_STATUS);
		ret = scr24x_रुको_पढ़ोy(dev);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	ret = count;
out:
	mutex_unlock(&dev->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations scr24x_fops = अणु
	.owner		= THIS_MODULE,
	.पढ़ो		= scr24x_पढ़ो,
	.ग_लिखो		= scr24x_ग_लिखो,
	.खोलो		= scr24x_खोलो,
	.release	= scr24x_release,
	.llseek		= no_llseek,
पूर्ण;

अटल पूर्णांक scr24x_config_check(काष्ठा pcmcia_device *link, व्योम *priv_data)
अणु
	अगर (resource_size(link->resource[PCMCIA_IOPORT_0]) != 0x11)
		वापस -ENODEV;
	वापस pcmcia_request_io(link);
पूर्ण

अटल पूर्णांक scr24x_probe(काष्ठा pcmcia_device *link)
अणु
	काष्ठा scr24x_dev *dev;
	पूर्णांक ret;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	dev->devno = find_first_zero_bit(scr24x_minors, SCR24X_DEVS);
	अगर (dev->devno >= SCR24X_DEVS) अणु
		ret = -EBUSY;
		जाओ err;
	पूर्ण

	mutex_init(&dev->lock);
	kref_init(&dev->refcnt);

	link->priv = dev;
	link->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;

	ret = pcmcia_loop_config(link, scr24x_config_check, शून्य);
	अगर (ret < 0)
		जाओ err;

	dev->dev = &link->dev;
	dev->regs = devm_ioport_map(&link->dev,
				link->resource[PCMCIA_IOPORT_0]->start,
				resource_size(link->resource[PCMCIA_IOPORT_0]));
	अगर (!dev->regs) अणु
		ret = -EIO;
		जाओ err;
	पूर्ण

	cdev_init(&dev->c_dev, &scr24x_fops);
	dev->c_dev.owner = THIS_MODULE;
	dev->c_dev.ops = &scr24x_fops;
	ret = cdev_add(&dev->c_dev, MKDEV(MAJOR(scr24x_devt), dev->devno), 1);
	अगर (ret < 0)
		जाओ err;

	ret = pcmcia_enable_device(link);
	अगर (ret < 0) अणु
		pcmcia_disable_device(link);
		जाओ err;
	पूर्ण

	device_create(scr24x_class, शून्य, MKDEV(MAJOR(scr24x_devt), dev->devno),
		      शून्य, "scr24x%d", dev->devno);

	dev_info(&link->dev, "SCR24x Chip Card Interface\n");
	वापस 0;

err:
	अगर (dev->devno < SCR24X_DEVS)
		clear_bit(dev->devno, scr24x_minors);
	kमुक्त (dev);
	वापस ret;
पूर्ण

अटल व्योम scr24x_हटाओ(काष्ठा pcmcia_device *link)
अणु
	काष्ठा scr24x_dev *dev = (काष्ठा scr24x_dev *)link->priv;

	device_destroy(scr24x_class, MKDEV(MAJOR(scr24x_devt), dev->devno));
	mutex_lock(&dev->lock);
	pcmcia_disable_device(link);
	cdev_del(&dev->c_dev);
	clear_bit(dev->devno, scr24x_minors);
	dev->dev = शून्य;
	mutex_unlock(&dev->lock);

	kref_put(&dev->refcnt, scr24x_delete);
पूर्ण

अटल स्थिर काष्ठा pcmcia_device_id scr24x_ids[] = अणु
	PCMCIA_DEVICE_PROD_ID12("HP", "PC Card Smart Card Reader",
					0x53cb94f9, 0xbfdf89a5),
	PCMCIA_DEVICE_PROD_ID1("SCR241 PCMCIA", 0x6271efa3),
	PCMCIA_DEVICE_PROD_ID1("SCR243 PCMCIA", 0x2054e8de),
	PCMCIA_DEVICE_PROD_ID1("SCR24x PCMCIA", 0x54a33665),
	PCMCIA_DEVICE_शून्य
पूर्ण;
MODULE_DEVICE_TABLE(pcmcia, scr24x_ids);

अटल काष्ठा pcmcia_driver scr24x_driver = अणु
	.owner		= THIS_MODULE,
	.name		= "scr24x_cs",
	.probe		= scr24x_probe,
	.हटाओ		= scr24x_हटाओ,
	.id_table	= scr24x_ids,
पूर्ण;

अटल पूर्णांक __init scr24x_init(व्योम)
अणु
	पूर्णांक ret;

	scr24x_class = class_create(THIS_MODULE, "scr24x");
	अगर (IS_ERR(scr24x_class))
		वापस PTR_ERR(scr24x_class);

	ret = alloc_chrdev_region(&scr24x_devt, 0, SCR24X_DEVS, "scr24x");
	अगर (ret < 0)  अणु
		class_destroy(scr24x_class);
		वापस ret;
	पूर्ण

	ret = pcmcia_रेजिस्टर_driver(&scr24x_driver);
	अगर (ret < 0) अणु
		unरेजिस्टर_chrdev_region(scr24x_devt, SCR24X_DEVS);
		class_destroy(scr24x_class);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __निकास scr24x_निकास(व्योम)
अणु
	pcmcia_unरेजिस्टर_driver(&scr24x_driver);
	unरेजिस्टर_chrdev_region(scr24x_devt, SCR24X_DEVS);
	class_destroy(scr24x_class);
पूर्ण

module_init(scr24x_init);
module_निकास(scr24x_निकास);

MODULE_AUTHOR("Lubomir Rintel");
MODULE_DESCRIPTION("SCR24x PCMCIA Smart Card Reader Driver");
MODULE_LICENSE("GPL");
