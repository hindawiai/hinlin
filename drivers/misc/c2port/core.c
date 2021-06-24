<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Silicon Lअसल C2 port core Linux support
 *
 *  Copyright (c) 2007 Roकरोlfo Giometti <giometti@linux.it>
 *  Copyright (c) 2007 Eurotech S.p.A. <info@eurotech.it>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/delay.h>
#समावेश <linux/idr.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश <linux/c2port.h>

#घोषणा DRIVER_NAME             "c2port"
#घोषणा DRIVER_VERSION          "0.51.0"

अटल DEFINE_SPINLOCK(c2port_idr_lock);
अटल DEFINE_IDR(c2port_idr);

/*
 * Local variables
 */

अटल काष्ठा class *c2port_class;

/*
 * C2 रेजिस्टरs & commands defines
 */

/* C2 रेजिस्टरs */
#घोषणा C2PORT_DEVICEID		0x00
#घोषणा C2PORT_REVID		0x01
#घोषणा C2PORT_FPCTL		0x02
#घोषणा C2PORT_FPDAT		0xB4

/* C2 पूर्णांकerface commands */
#घोषणा C2PORT_GET_VERSION	0x01
#घोषणा C2PORT_DEVICE_ERASE	0x03
#घोषणा C2PORT_BLOCK_READ	0x06
#घोषणा C2PORT_BLOCK_WRITE	0x07
#घोषणा C2PORT_PAGE_ERASE	0x08

/* C2 status वापस codes */
#घोषणा C2PORT_INVALID_COMMAND	0x00
#घोषणा C2PORT_COMMAND_FAILED	0x02
#घोषणा C2PORT_COMMAND_OK	0x0d

/*
 * C2 port low level संकेत managements
 */

अटल व्योम c2port_reset(काष्ठा c2port_device *dev)
अणु
	काष्ठा c2port_ops *ops = dev->ops;

	/* To reset the device we have to keep घड़ी line low क्रम at least
	 * 20us.
	 */
	local_irq_disable();
	ops->c2ck_set(dev, 0);
	udelay(25);
	ops->c2ck_set(dev, 1);
	local_irq_enable();

	udelay(1);
पूर्ण

अटल व्योम c2port_strobe_ck(काष्ठा c2port_device *dev)
अणु
	काष्ठा c2port_ops *ops = dev->ops;

	/* During hi-low-hi transition we disable local IRQs to aव्योम
	 * पूर्णांकerructions since C2 port specअगरication says that it must be
	 * लघुer than 5us, otherwise the microcontroller may consider
	 * it as a reset संकेत!
	 */
	local_irq_disable();
	ops->c2ck_set(dev, 0);
	udelay(1);
	ops->c2ck_set(dev, 1);
	local_irq_enable();

	udelay(1);
पूर्ण

/*
 * C2 port basic functions
 */

अटल व्योम c2port_ग_लिखो_ar(काष्ठा c2port_device *dev, u8 addr)
अणु
	काष्ठा c2port_ops *ops = dev->ops;
	पूर्णांक i;

	/* START field */
	c2port_strobe_ck(dev);

	/* INS field (11b, LSB first) */
	ops->c2d_dir(dev, 0);
	ops->c2d_set(dev, 1);
	c2port_strobe_ck(dev);
	ops->c2d_set(dev, 1);
	c2port_strobe_ck(dev);

	/* ADDRESS field */
	क्रम (i = 0; i < 8; i++) अणु
		ops->c2d_set(dev, addr & 0x01);
		c2port_strobe_ck(dev);

		addr >>= 1;
	पूर्ण

	/* STOP field */
	ops->c2d_dir(dev, 1);
	c2port_strobe_ck(dev);
पूर्ण

अटल पूर्णांक c2port_पढ़ो_ar(काष्ठा c2port_device *dev, u8 *addr)
अणु
	काष्ठा c2port_ops *ops = dev->ops;
	पूर्णांक i;

	/* START field */
	c2port_strobe_ck(dev);

	/* INS field (10b, LSB first) */
	ops->c2d_dir(dev, 0);
	ops->c2d_set(dev, 0);
	c2port_strobe_ck(dev);
	ops->c2d_set(dev, 1);
	c2port_strobe_ck(dev);

	/* ADDRESS field */
	ops->c2d_dir(dev, 1);
	*addr = 0;
	क्रम (i = 0; i < 8; i++) अणु
		*addr >>= 1;	/* shअगरt in 8-bit ADDRESS field LSB first */

		c2port_strobe_ck(dev);
		अगर (ops->c2d_get(dev))
			*addr |= 0x80;
	पूर्ण

	/* STOP field */
	c2port_strobe_ck(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक c2port_ग_लिखो_dr(काष्ठा c2port_device *dev, u8 data)
अणु
	काष्ठा c2port_ops *ops = dev->ops;
	पूर्णांक समयout, i;

	/* START field */
	c2port_strobe_ck(dev);

	/* INS field (01b, LSB first) */
	ops->c2d_dir(dev, 0);
	ops->c2d_set(dev, 1);
	c2port_strobe_ck(dev);
	ops->c2d_set(dev, 0);
	c2port_strobe_ck(dev);

	/* LENGTH field (00b, LSB first -> 1 byte) */
	ops->c2d_set(dev, 0);
	c2port_strobe_ck(dev);
	ops->c2d_set(dev, 0);
	c2port_strobe_ck(dev);

	/* DATA field */
	क्रम (i = 0; i < 8; i++) अणु
		ops->c2d_set(dev, data & 0x01);
		c2port_strobe_ck(dev);

		data >>= 1;
	पूर्ण

	/* WAIT field */
	ops->c2d_dir(dev, 1);
	समयout = 20;
	करो अणु
		c2port_strobe_ck(dev);
		अगर (ops->c2d_get(dev))
			अवरोध;

		udelay(1);
	पूर्ण जबतक (--समयout > 0);
	अगर (समयout == 0)
		वापस -EIO;

	/* STOP field */
	c2port_strobe_ck(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक c2port_पढ़ो_dr(काष्ठा c2port_device *dev, u8 *data)
अणु
	काष्ठा c2port_ops *ops = dev->ops;
	पूर्णांक समयout, i;

	/* START field */
	c2port_strobe_ck(dev);

	/* INS field (00b, LSB first) */
	ops->c2d_dir(dev, 0);
	ops->c2d_set(dev, 0);
	c2port_strobe_ck(dev);
	ops->c2d_set(dev, 0);
	c2port_strobe_ck(dev);

	/* LENGTH field (00b, LSB first -> 1 byte) */
	ops->c2d_set(dev, 0);
	c2port_strobe_ck(dev);
	ops->c2d_set(dev, 0);
	c2port_strobe_ck(dev);

	/* WAIT field */
	ops->c2d_dir(dev, 1);
	समयout = 20;
	करो अणु
		c2port_strobe_ck(dev);
		अगर (ops->c2d_get(dev))
			अवरोध;

		udelay(1);
	पूर्ण जबतक (--समयout > 0);
	अगर (समयout == 0)
		वापस -EIO;

	/* DATA field */
	*data = 0;
	क्रम (i = 0; i < 8; i++) अणु
		*data >>= 1;	/* shअगरt in 8-bit DATA field LSB first */

		c2port_strobe_ck(dev);
		अगर (ops->c2d_get(dev))
			*data |= 0x80;
	पूर्ण

	/* STOP field */
	c2port_strobe_ck(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक c2port_poll_in_busy(काष्ठा c2port_device *dev)
अणु
	u8 addr;
	पूर्णांक ret, समयout = 20;

	करो अणु
		ret = (c2port_पढ़ो_ar(dev, &addr));
		अगर (ret < 0)
			वापस -EIO;

		अगर (!(addr & 0x02))
			अवरोध;

		udelay(1);
	पूर्ण जबतक (--समयout > 0);
	अगर (समयout == 0)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक c2port_poll_out_पढ़ोy(काष्ठा c2port_device *dev)
अणु
	u8 addr;
	पूर्णांक ret, समयout = 10000; /* erase flash needs दीर्घ समय... */

	करो अणु
		ret = (c2port_पढ़ो_ar(dev, &addr));
		अगर (ret < 0)
			वापस -EIO;

		अगर (addr & 0x01)
			अवरोध;

		udelay(1);
	पूर्ण जबतक (--समयout > 0);
	अगर (समयout == 0)
		वापस -EIO;

	वापस 0;
पूर्ण

/*
 * sysfs methods
 */

अटल sमाप_प्रकार c2port_show_name(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा c2port_device *c2dev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", c2dev->name);
पूर्ण
अटल DEVICE_ATTR(name, 0444, c2port_show_name, शून्य);

अटल sमाप_प्रकार c2port_show_flash_blocks_num(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा c2port_device *c2dev = dev_get_drvdata(dev);
	काष्ठा c2port_ops *ops = c2dev->ops;

	वापस प्र_लिखो(buf, "%d\n", ops->blocks_num);
पूर्ण
अटल DEVICE_ATTR(flash_blocks_num, 0444, c2port_show_flash_blocks_num, शून्य);

अटल sमाप_प्रकार c2port_show_flash_block_size(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा c2port_device *c2dev = dev_get_drvdata(dev);
	काष्ठा c2port_ops *ops = c2dev->ops;

	वापस प्र_लिखो(buf, "%d\n", ops->block_size);
पूर्ण
अटल DEVICE_ATTR(flash_block_size, 0444, c2port_show_flash_block_size, शून्य);

अटल sमाप_प्रकार c2port_show_flash_size(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा c2port_device *c2dev = dev_get_drvdata(dev);
	काष्ठा c2port_ops *ops = c2dev->ops;

	वापस प्र_लिखो(buf, "%d\n", ops->blocks_num * ops->block_size);
पूर्ण
अटल DEVICE_ATTR(flash_size, 0444, c2port_show_flash_size, शून्य);

अटल sमाप_प्रकार access_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   अक्षर *buf)
अणु
	काष्ठा c2port_device *c2dev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", c2dev->access);
पूर्ण

अटल sमाप_प्रकार access_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा c2port_device *c2dev = dev_get_drvdata(dev);
	काष्ठा c2port_ops *ops = c2dev->ops;
	पूर्णांक status, ret;

	ret = माला_पूछो(buf, "%d", &status);
	अगर (ret != 1)
		वापस -EINVAL;

	mutex_lock(&c2dev->mutex);

	c2dev->access = !!status;

	/* If access is "on" घड़ी should be HIGH _beक्रमe_ setting the line
	 * as output and data line should be set as INPUT anyway */
	अगर (c2dev->access)
		ops->c2ck_set(c2dev, 1);
	ops->access(c2dev, c2dev->access);
	अगर (c2dev->access)
		ops->c2d_dir(c2dev, 1);

	mutex_unlock(&c2dev->mutex);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(access);

अटल sमाप_प्रकार c2port_store_reset(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा c2port_device *c2dev = dev_get_drvdata(dev);

	/* Check the device access status */
	अगर (!c2dev->access)
		वापस -EBUSY;

	mutex_lock(&c2dev->mutex);

	c2port_reset(c2dev);
	c2dev->flash_access = 0;

	mutex_unlock(&c2dev->mutex);

	वापस count;
पूर्ण
अटल DEVICE_ATTR(reset, 0200, शून्य, c2port_store_reset);

अटल sमाप_प्रकार __c2port_show_dev_id(काष्ठा c2port_device *dev, अक्षर *buf)
अणु
	u8 data;
	पूर्णांक ret;

	/* Select DEVICEID रेजिस्टर क्रम C2 data रेजिस्टर accesses */
	c2port_ग_लिखो_ar(dev, C2PORT_DEVICEID);

	/* Read and वापस the device ID रेजिस्टर */
	ret = c2port_पढ़ो_dr(dev, &data);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", data);
पूर्ण

अटल sमाप_प्रकार c2port_show_dev_id(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा c2port_device *c2dev = dev_get_drvdata(dev);
	sमाप_प्रकार ret;

	/* Check the device access status */
	अगर (!c2dev->access)
		वापस -EBUSY;

	mutex_lock(&c2dev->mutex);
	ret = __c2port_show_dev_id(c2dev, buf);
	mutex_unlock(&c2dev->mutex);

	अगर (ret < 0)
		dev_err(dev, "cannot read from %s\n", c2dev->name);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR(dev_id, 0444, c2port_show_dev_id, शून्य);

अटल sमाप_प्रकार __c2port_show_rev_id(काष्ठा c2port_device *dev, अक्षर *buf)
अणु
	u8 data;
	पूर्णांक ret;

	/* Select REVID रेजिस्टर क्रम C2 data रेजिस्टर accesses */
	c2port_ग_लिखो_ar(dev, C2PORT_REVID);

	/* Read and वापस the revision ID रेजिस्टर */
	ret = c2port_पढ़ो_dr(dev, &data);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", data);
पूर्ण

अटल sमाप_प्रकार c2port_show_rev_id(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा c2port_device *c2dev = dev_get_drvdata(dev);
	sमाप_प्रकार ret;

	/* Check the device access status */
	अगर (!c2dev->access)
		वापस -EBUSY;

	mutex_lock(&c2dev->mutex);
	ret = __c2port_show_rev_id(c2dev, buf);
	mutex_unlock(&c2dev->mutex);

	अगर (ret < 0)
		dev_err(c2dev->dev, "cannot read from %s\n", c2dev->name);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR(rev_id, 0444, c2port_show_rev_id, शून्य);

अटल sमाप_प्रकार c2port_show_flash_access(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा c2port_device *c2dev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", c2dev->flash_access);
पूर्ण

अटल sमाप_प्रकार __c2port_store_flash_access(काष्ठा c2port_device *dev,
						पूर्णांक status)
अणु
	पूर्णांक ret;

	/* Check the device access status */
	अगर (!dev->access)
		वापस -EBUSY;

	dev->flash_access = !!status;

	/* If flash_access is off we have nothing to करो... */
	अगर (dev->flash_access == 0)
		वापस 0;

	/* Target the C2 flash programming control रेजिस्टर क्रम C2 data
	 * रेजिस्टर access */
	c2port_ग_लिखो_ar(dev, C2PORT_FPCTL);

	/* Write the first keycode to enable C2 Flash programming */
	ret = c2port_ग_लिखो_dr(dev, 0x02);
	अगर (ret < 0)
		वापस ret;

	/* Write the second keycode to enable C2 Flash programming */
	ret = c2port_ग_लिखो_dr(dev, 0x01);
	अगर (ret < 0)
		वापस ret;

	/* Delay क्रम at least 20ms to ensure the target is पढ़ोy क्रम
	 * C2 flash programming */
	mdelay(25);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार c2port_store_flash_access(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा c2port_device *c2dev = dev_get_drvdata(dev);
	पूर्णांक status;
	sमाप_प्रकार ret;

	ret = माला_पूछो(buf, "%d", &status);
	अगर (ret != 1)
		वापस -EINVAL;

	mutex_lock(&c2dev->mutex);
	ret = __c2port_store_flash_access(c2dev, status);
	mutex_unlock(&c2dev->mutex);

	अगर (ret < 0) अणु
		dev_err(c2dev->dev, "cannot enable %s flash programming\n",
			c2dev->name);
		वापस ret;
	पूर्ण

	वापस count;
पूर्ण
अटल DEVICE_ATTR(flash_access, 0644, c2port_show_flash_access,
		   c2port_store_flash_access);

अटल sमाप_प्रकार __c2port_ग_लिखो_flash_erase(काष्ठा c2port_device *dev)
अणु
	u8 status;
	पूर्णांक ret;

	/* Target the C2 flash programming data रेजिस्टर क्रम C2 data रेजिस्टर
	 * access.
	 */
	c2port_ग_लिखो_ar(dev, C2PORT_FPDAT);

	/* Send device erase command */
	c2port_ग_लिखो_dr(dev, C2PORT_DEVICE_ERASE);

	/* Wait क्रम input acknowledge */
	ret = c2port_poll_in_busy(dev);
	अगर (ret < 0)
		वापस ret;

	/* Should check status beक्रमe starting FLASH access sequence */

	/* Wait क्रम status inक्रमmation */
	ret = c2port_poll_out_पढ़ोy(dev);
	अगर (ret < 0)
		वापस ret;

	/* Read flash programming पूर्णांकerface status */
	ret = c2port_पढ़ो_dr(dev, &status);
	अगर (ret < 0)
		वापस ret;
	अगर (status != C2PORT_COMMAND_OK)
		वापस -EBUSY;

	/* Send a three-byte arming sequence to enable the device erase.
	 * If the sequence is not received correctly, the command will be
	 * ignored.
	 * Sequence is: 0xde, 0xad, 0xa5.
	 */
	c2port_ग_लिखो_dr(dev, 0xde);
	ret = c2port_poll_in_busy(dev);
	अगर (ret < 0)
		वापस ret;
	c2port_ग_लिखो_dr(dev, 0xad);
	ret = c2port_poll_in_busy(dev);
	अगर (ret < 0)
		वापस ret;
	c2port_ग_लिखो_dr(dev, 0xa5);
	ret = c2port_poll_in_busy(dev);
	अगर (ret < 0)
		वापस ret;

	ret = c2port_poll_out_पढ़ोy(dev);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार c2port_store_flash_erase(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा c2port_device *c2dev = dev_get_drvdata(dev);
	पूर्णांक ret;

	/* Check the device and flash access status */
	अगर (!c2dev->access || !c2dev->flash_access)
		वापस -EBUSY;

	mutex_lock(&c2dev->mutex);
	ret = __c2port_ग_लिखो_flash_erase(c2dev);
	mutex_unlock(&c2dev->mutex);

	अगर (ret < 0) अणु
		dev_err(c2dev->dev, "cannot erase %s flash\n", c2dev->name);
		वापस ret;
	पूर्ण

	वापस count;
पूर्ण
अटल DEVICE_ATTR(flash_erase, 0200, शून्य, c2port_store_flash_erase);

अटल sमाप_प्रकार __c2port_पढ़ो_flash_data(काष्ठा c2port_device *dev,
				अक्षर *buffer, loff_t offset, माप_प्रकार count)
अणु
	काष्ठा c2port_ops *ops = dev->ops;
	u8 status, nपढ़ो = 128;
	पूर्णांक i, ret;

	/* Check क्रम flash end */
	अगर (offset >= ops->block_size * ops->blocks_num)
		वापस 0;

	अगर (ops->block_size * ops->blocks_num - offset < nपढ़ो)
		nपढ़ो = ops->block_size * ops->blocks_num - offset;
	अगर (count < nपढ़ो)
		nपढ़ो = count;
	अगर (nपढ़ो == 0)
		वापस nपढ़ो;

	/* Target the C2 flash programming data रेजिस्टर क्रम C2 data रेजिस्टर
	 * access */
	c2port_ग_लिखो_ar(dev, C2PORT_FPDAT);

	/* Send flash block पढ़ो command */
	c2port_ग_लिखो_dr(dev, C2PORT_BLOCK_READ);

	/* Wait क्रम input acknowledge */
	ret = c2port_poll_in_busy(dev);
	अगर (ret < 0)
		वापस ret;

	/* Should check status beक्रमe starting FLASH access sequence */

	/* Wait क्रम status inक्रमmation */
	ret = c2port_poll_out_पढ़ोy(dev);
	अगर (ret < 0)
		वापस ret;

	/* Read flash programming पूर्णांकerface status */
	ret = c2port_पढ़ो_dr(dev, &status);
	अगर (ret < 0)
		वापस ret;
	अगर (status != C2PORT_COMMAND_OK)
		वापस -EBUSY;

	/* Send address high byte */
	c2port_ग_लिखो_dr(dev, offset >> 8);
	ret = c2port_poll_in_busy(dev);
	अगर (ret < 0)
		वापस ret;

	/* Send address low byte */
	c2port_ग_लिखो_dr(dev, offset & 0x00ff);
	ret = c2port_poll_in_busy(dev);
	अगर (ret < 0)
		वापस ret;

	/* Send address block size */
	c2port_ग_लिखो_dr(dev, nपढ़ो);
	ret = c2port_poll_in_busy(dev);
	अगर (ret < 0)
		वापस ret;

	/* Should check status beक्रमe पढ़ोing FLASH block */

	/* Wait क्रम status inक्रमmation */
	ret = c2port_poll_out_पढ़ोy(dev);
	अगर (ret < 0)
		वापस ret;

	/* Read flash programming पूर्णांकerface status */
	ret = c2port_पढ़ो_dr(dev, &status);
	अगर (ret < 0)
		वापस ret;
	अगर (status != C2PORT_COMMAND_OK)
		वापस -EBUSY;

	/* Read flash block */
	क्रम (i = 0; i < nपढ़ो; i++) अणु
		ret = c2port_poll_out_पढ़ोy(dev);
		अगर (ret < 0)
			वापस ret;

		ret = c2port_पढ़ो_dr(dev, buffer+i);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस nपढ़ो;
पूर्ण

अटल sमाप_प्रकार c2port_पढ़ो_flash_data(काष्ठा file *filp, काष्ठा kobject *kobj,
				काष्ठा bin_attribute *attr,
				अक्षर *buffer, loff_t offset, माप_प्रकार count)
अणु
	काष्ठा c2port_device *c2dev = dev_get_drvdata(kobj_to_dev(kobj));
	sमाप_प्रकार ret;

	/* Check the device and flash access status */
	अगर (!c2dev->access || !c2dev->flash_access)
		वापस -EBUSY;

	mutex_lock(&c2dev->mutex);
	ret = __c2port_पढ़ो_flash_data(c2dev, buffer, offset, count);
	mutex_unlock(&c2dev->mutex);

	अगर (ret < 0)
		dev_err(c2dev->dev, "cannot read %s flash\n", c2dev->name);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार __c2port_ग_लिखो_flash_data(काष्ठा c2port_device *dev,
				अक्षर *buffer, loff_t offset, माप_प्रकार count)
अणु
	काष्ठा c2port_ops *ops = dev->ops;
	u8 status, nग_लिखो = 128;
	पूर्णांक i, ret;

	अगर (nग_लिखो > count)
		nग_लिखो = count;
	अगर (ops->block_size * ops->blocks_num - offset < nग_लिखो)
		nग_लिखो = ops->block_size * ops->blocks_num - offset;

	/* Check क्रम flash end */
	अगर (offset >= ops->block_size * ops->blocks_num)
		वापस -EINVAL;

	/* Target the C2 flash programming data रेजिस्टर क्रम C2 data रेजिस्टर
	 * access */
	c2port_ग_लिखो_ar(dev, C2PORT_FPDAT);

	/* Send flash block ग_लिखो command */
	c2port_ग_लिखो_dr(dev, C2PORT_BLOCK_WRITE);

	/* Wait क्रम input acknowledge */
	ret = c2port_poll_in_busy(dev);
	अगर (ret < 0)
		वापस ret;

	/* Should check status beक्रमe starting FLASH access sequence */

	/* Wait क्रम status inक्रमmation */
	ret = c2port_poll_out_पढ़ोy(dev);
	अगर (ret < 0)
		वापस ret;

	/* Read flash programming पूर्णांकerface status */
	ret = c2port_पढ़ो_dr(dev, &status);
	अगर (ret < 0)
		वापस ret;
	अगर (status != C2PORT_COMMAND_OK)
		वापस -EBUSY;

	/* Send address high byte */
	c2port_ग_लिखो_dr(dev, offset >> 8);
	ret = c2port_poll_in_busy(dev);
	अगर (ret < 0)
		वापस ret;

	/* Send address low byte */
	c2port_ग_लिखो_dr(dev, offset & 0x00ff);
	ret = c2port_poll_in_busy(dev);
	अगर (ret < 0)
		वापस ret;

	/* Send address block size */
	c2port_ग_लिखो_dr(dev, nग_लिखो);
	ret = c2port_poll_in_busy(dev);
	अगर (ret < 0)
		वापस ret;

	/* Should check status beक्रमe writing FLASH block */

	/* Wait क्रम status inक्रमmation */
	ret = c2port_poll_out_पढ़ोy(dev);
	अगर (ret < 0)
		वापस ret;

	/* Read flash programming पूर्णांकerface status */
	ret = c2port_पढ़ो_dr(dev, &status);
	अगर (ret < 0)
		वापस ret;
	अगर (status != C2PORT_COMMAND_OK)
		वापस -EBUSY;

	/* Write flash block */
	क्रम (i = 0; i < nग_लिखो; i++) अणु
		ret = c2port_ग_लिखो_dr(dev, *(buffer+i));
		अगर (ret < 0)
			वापस ret;

		ret = c2port_poll_in_busy(dev);
		अगर (ret < 0)
			वापस ret;

	पूर्ण

	/* Wait क्रम last flash ग_लिखो to complete */
	ret = c2port_poll_out_पढ़ोy(dev);
	अगर (ret < 0)
		वापस ret;

	वापस nग_लिखो;
पूर्ण

अटल sमाप_प्रकार c2port_ग_लिखो_flash_data(काष्ठा file *filp, काष्ठा kobject *kobj,
				काष्ठा bin_attribute *attr,
				अक्षर *buffer, loff_t offset, माप_प्रकार count)
अणु
	काष्ठा c2port_device *c2dev = dev_get_drvdata(kobj_to_dev(kobj));
	पूर्णांक ret;

	/* Check the device access status */
	अगर (!c2dev->access || !c2dev->flash_access)
		वापस -EBUSY;

	mutex_lock(&c2dev->mutex);
	ret = __c2port_ग_लिखो_flash_data(c2dev, buffer, offset, count);
	mutex_unlock(&c2dev->mutex);

	अगर (ret < 0)
		dev_err(c2dev->dev, "cannot write %s flash\n", c2dev->name);

	वापस ret;
पूर्ण
/* size is computed at run-समय */
अटल BIN_ATTR(flash_data, 0644, c2port_पढ़ो_flash_data,
		c2port_ग_लिखो_flash_data, 0);

/*
 * Class attributes
 */
अटल काष्ठा attribute *c2port_attrs[] = अणु
	&dev_attr_name.attr,
	&dev_attr_flash_blocks_num.attr,
	&dev_attr_flash_block_size.attr,
	&dev_attr_flash_size.attr,
	&dev_attr_access.attr,
	&dev_attr_reset.attr,
	&dev_attr_dev_id.attr,
	&dev_attr_rev_id.attr,
	&dev_attr_flash_access.attr,
	&dev_attr_flash_erase.attr,
	शून्य,
पूर्ण;

अटल काष्ठा bin_attribute *c2port_bin_attrs[] = अणु
	&bin_attr_flash_data,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group c2port_group = अणु
	.attrs = c2port_attrs,
	.bin_attrs = c2port_bin_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *c2port_groups[] = अणु
	&c2port_group,
	शून्य,
पूर्ण;

/*
 * Exported functions
 */

काष्ठा c2port_device *c2port_device_रेजिस्टर(अक्षर *name,
					काष्ठा c2port_ops *ops, व्योम *devdata)
अणु
	काष्ठा c2port_device *c2dev;
	पूर्णांक ret;

	अगर (unlikely(!ops) || unlikely(!ops->access) || \
		unlikely(!ops->c2d_dir) || unlikely(!ops->c2ck_set) || \
		unlikely(!ops->c2d_get) || unlikely(!ops->c2d_set))
		वापस ERR_PTR(-EINVAL);

	c2dev = kzalloc(माप(काष्ठा c2port_device), GFP_KERNEL);
	अगर (unlikely(!c2dev))
		वापस ERR_PTR(-ENOMEM);

	idr_preload(GFP_KERNEL);
	spin_lock_irq(&c2port_idr_lock);
	ret = idr_alloc(&c2port_idr, c2dev, 0, 0, GFP_NOWAIT);
	spin_unlock_irq(&c2port_idr_lock);
	idr_preload_end();

	अगर (ret < 0)
		जाओ error_idr_alloc;
	c2dev->id = ret;

	bin_attr_flash_data.size = ops->blocks_num * ops->block_size;

	c2dev->dev = device_create(c2port_class, शून्य, 0, c2dev,
				   "c2port%d", c2dev->id);
	अगर (IS_ERR(c2dev->dev)) अणु
		ret = PTR_ERR(c2dev->dev);
		जाओ error_device_create;
	पूर्ण
	dev_set_drvdata(c2dev->dev, c2dev);

	म_नकलन(c2dev->name, name, C2PORT_NAME_LEN - 1);
	c2dev->ops = ops;
	mutex_init(&c2dev->mutex);

	/* By शेष C2 port access is off */
	c2dev->access = c2dev->flash_access = 0;
	ops->access(c2dev, 0);

	dev_info(c2dev->dev, "C2 port %s added\n", name);
	dev_info(c2dev->dev, "%s flash has %d blocks x %d bytes "
				"(%d bytes total)\n",
				name, ops->blocks_num, ops->block_size,
				ops->blocks_num * ops->block_size);

	वापस c2dev;

error_device_create:
	spin_lock_irq(&c2port_idr_lock);
	idr_हटाओ(&c2port_idr, c2dev->id);
	spin_unlock_irq(&c2port_idr_lock);

error_idr_alloc:
	kमुक्त(c2dev);

	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL(c2port_device_रेजिस्टर);

व्योम c2port_device_unरेजिस्टर(काष्ठा c2port_device *c2dev)
अणु
	अगर (!c2dev)
		वापस;

	dev_info(c2dev->dev, "C2 port %s removed\n", c2dev->name);

	spin_lock_irq(&c2port_idr_lock);
	idr_हटाओ(&c2port_idr, c2dev->id);
	spin_unlock_irq(&c2port_idr_lock);

	device_destroy(c2port_class, c2dev->id);

	kमुक्त(c2dev);
पूर्ण
EXPORT_SYMBOL(c2port_device_unरेजिस्टर);

/*
 * Module stuff
 */

अटल पूर्णांक __init c2port_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "Silicon Labs C2 port support v. " DRIVER_VERSION
		" - (C) 2007 Rodolfo Giometti\n");

	c2port_class = class_create(THIS_MODULE, "c2port");
	अगर (IS_ERR(c2port_class)) अणु
		prपूर्णांकk(KERN_ERR "c2port: failed to allocate class\n");
		वापस PTR_ERR(c2port_class);
	पूर्ण
	c2port_class->dev_groups = c2port_groups;

	वापस 0;
पूर्ण

अटल व्योम __निकास c2port_निकास(व्योम)
अणु
	class_destroy(c2port_class);
पूर्ण

module_init(c2port_init);
module_निकास(c2port_निकास);

MODULE_AUTHOR("Rodolfo Giometti <giometti@linux.it>");
MODULE_DESCRIPTION("Silicon Labs C2 port support v. " DRIVER_VERSION);
MODULE_LICENSE("GPL");
