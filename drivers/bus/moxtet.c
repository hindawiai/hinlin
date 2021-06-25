<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Turris Mox module configuration bus driver
 *
 * Copyright (C) 2019 Marek Behथजn <kabel@kernel.org>
 */

#समावेश <dt-bindings/bus/moxtet.h>
#समावेश <linux/bitops.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/moxtet.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/spi/spi.h>

/*
 * @name:	module name क्रम sysfs
 * @hwirq_base:	base index क्रम IRQ क्रम this module (-1 अगर no IRQs)
 * @nirqs:	how many पूर्णांकerrupts करोes the shअगरt रेजिस्टर provide
 * @desc:	module description क्रम kernel log
 */
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	पूर्णांक hwirq_base;
	पूर्णांक nirqs;
	स्थिर अक्षर *desc;
पूर्ण mox_module_table[] = अणु
	/* करो not change order of this array! */
	अणु शून्य,		 0,			0, शून्य पूर्ण,
	अणु "sfp",	-1,			0, "MOX D (SFP cage)" पूर्ण,
	अणु "pci",	MOXTET_IRQ_PCI,		1, "MOX B (Mini-PCIe)" पूर्ण,
	अणु "topaz",	MOXTET_IRQ_TOPAZ,	1, "MOX C (4 port switch)" पूर्ण,
	अणु "peridot",	MOXTET_IRQ_PERIDOT(0),	1, "MOX E (8 port switch)" पूर्ण,
	अणु "usb3",	MOXTET_IRQ_USB3,	2, "MOX F (USB 3.0)" पूर्ण,
	अणु "pci-bridge",	-1,			0, "MOX G (Mini-PCIe bridge)" पूर्ण,
पूर्ण;

अटल अंतरभूत bool mox_module_known(अचिन्हित पूर्णांक id)
अणु
	वापस id >= TURRIS_MOX_MODULE_FIRST && id <= TURRIS_MOX_MODULE_LAST;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *mox_module_name(अचिन्हित पूर्णांक id)
अणु
	अगर (mox_module_known(id))
		वापस mox_module_table[id].name;
	अन्यथा
		वापस "unknown";
पूर्ण

#घोषणा DEF_MODULE_ATTR(name, fmt, ...)					\
अटल sमाप_प्रकार								\
module_##name##_show(काष्ठा device *dev, काष्ठा device_attribute *a,	\
		     अक्षर *buf)						\
अणु									\
	काष्ठा moxtet_device *mdev = to_moxtet_device(dev);		\
	वापस प्र_लिखो(buf, (fmt), __VA_ARGS__);			\
पूर्ण									\
अटल DEVICE_ATTR_RO(module_##name)

DEF_MODULE_ATTR(id, "0x%x\n", mdev->id);
DEF_MODULE_ATTR(name, "%s\n", mox_module_name(mdev->id));
DEF_MODULE_ATTR(description, "%s\n",
		mox_module_known(mdev->id) ? mox_module_table[mdev->id].desc
					   : "");

अटल काष्ठा attribute *moxtet_dev_attrs[] = अणु
	&dev_attr_module_id.attr,
	&dev_attr_module_name.attr,
	&dev_attr_module_description.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group moxtet_dev_group = अणु
	.attrs = moxtet_dev_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *moxtet_dev_groups[] = अणु
	&moxtet_dev_group,
	शून्य,
पूर्ण;

अटल पूर्णांक moxtet_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा moxtet_device *mdev = to_moxtet_device(dev);
	काष्ठा moxtet_driver *tdrv = to_moxtet_driver(drv);
	स्थिर क्रमागत turris_mox_module_id *t;

	अगर (of_driver_match_device(dev, drv))
		वापस 1;

	अगर (!tdrv->id_table)
		वापस 0;

	क्रम (t = tdrv->id_table; *t; ++t)
		अगर (*t == mdev->id)
			वापस 1;

	वापस 0;
पूर्ण

अटल काष्ठा bus_type moxtet_bus_type = अणु
	.name		= "moxtet",
	.dev_groups	= moxtet_dev_groups,
	.match		= moxtet_match,
पूर्ण;

पूर्णांक __moxtet_रेजिस्टर_driver(काष्ठा module *owner,
			     काष्ठा moxtet_driver *mdrv)
अणु
	mdrv->driver.owner = owner;
	mdrv->driver.bus = &moxtet_bus_type;
	वापस driver_रेजिस्टर(&mdrv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(__moxtet_रेजिस्टर_driver);

अटल पूर्णांक moxtet_dev_check(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा moxtet_device *mdev = to_moxtet_device(dev);
	काष्ठा moxtet_device *new_dev = data;

	अगर (mdev->moxtet == new_dev->moxtet && mdev->id == new_dev->id &&
	    mdev->idx == new_dev->idx)
		वापस -EBUSY;
	वापस 0;
पूर्ण

अटल व्योम moxtet_dev_release(काष्ठा device *dev)
अणु
	काष्ठा moxtet_device *mdev = to_moxtet_device(dev);

	put_device(mdev->moxtet->dev);
	kमुक्त(mdev);
पूर्ण

अटल काष्ठा moxtet_device *
moxtet_alloc_device(काष्ठा moxtet *moxtet)
अणु
	काष्ठा moxtet_device *dev;

	अगर (!get_device(moxtet->dev))
		वापस शून्य;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev) अणु
		put_device(moxtet->dev);
		वापस शून्य;
	पूर्ण

	dev->moxtet = moxtet;
	dev->dev.parent = moxtet->dev;
	dev->dev.bus = &moxtet_bus_type;
	dev->dev.release = moxtet_dev_release;

	device_initialize(&dev->dev);

	वापस dev;
पूर्ण

अटल पूर्णांक moxtet_add_device(काष्ठा moxtet_device *dev)
अणु
	अटल DEFINE_MUTEX(add_mutex);
	पूर्णांक ret;

	अगर (dev->idx >= TURRIS_MOX_MAX_MODULES || dev->id > 0xf)
		वापस -EINVAL;

	dev_set_name(&dev->dev, "moxtet-%s.%u", mox_module_name(dev->id),
		     dev->idx);

	mutex_lock(&add_mutex);

	ret = bus_क्रम_each_dev(&moxtet_bus_type, शून्य, dev,
			       moxtet_dev_check);
	अगर (ret)
		जाओ करोne;

	ret = device_add(&dev->dev);
	अगर (ret < 0)
		dev_err(dev->moxtet->dev, "can't add %s, status %d\n",
			dev_name(dev->moxtet->dev), ret);

करोne:
	mutex_unlock(&add_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक __unरेजिस्टर(काष्ठा device *dev, व्योम *null)
अणु
	अगर (dev->of_node) अणु
		of_node_clear_flag(dev->of_node, OF_POPULATED);
		of_node_put(dev->of_node);
	पूर्ण

	device_unरेजिस्टर(dev);

	वापस 0;
पूर्ण

अटल काष्ठा moxtet_device *
of_रेजिस्टर_moxtet_device(काष्ठा moxtet *moxtet, काष्ठा device_node *nc)
अणु
	काष्ठा moxtet_device *dev;
	u32 val;
	पूर्णांक ret;

	dev = moxtet_alloc_device(moxtet);
	अगर (!dev) अणु
		dev_err(moxtet->dev,
			"Moxtet device alloc error for %pOF\n", nc);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	ret = of_property_पढ़ो_u32(nc, "reg", &val);
	अगर (ret) अणु
		dev_err(moxtet->dev, "%pOF has no valid 'reg' property (%d)\n",
			nc, ret);
		जाओ err_put;
	पूर्ण

	dev->idx = val;

	अगर (dev->idx >= TURRIS_MOX_MAX_MODULES) अणु
		dev_err(moxtet->dev, "%pOF Moxtet address 0x%x out of range\n",
			nc, dev->idx);
		ret = -EINVAL;
		जाओ err_put;
	पूर्ण

	dev->id = moxtet->modules[dev->idx];

	अगर (!dev->id) अणु
		dev_err(moxtet->dev, "%pOF Moxtet address 0x%x is empty\n", nc,
			dev->idx);
		ret = -ENODEV;
		जाओ err_put;
	पूर्ण

	of_node_get(nc);
	dev->dev.of_node = nc;

	ret = moxtet_add_device(dev);
	अगर (ret) अणु
		dev_err(moxtet->dev,
			"Moxtet device register error for %pOF\n", nc);
		of_node_put(nc);
		जाओ err_put;
	पूर्ण

	वापस dev;

err_put:
	put_device(&dev->dev);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम of_रेजिस्टर_moxtet_devices(काष्ठा moxtet *moxtet)
अणु
	काष्ठा moxtet_device *dev;
	काष्ठा device_node *nc;

	अगर (!moxtet->dev->of_node)
		वापस;

	क्रम_each_available_child_of_node(moxtet->dev->of_node, nc) अणु
		अगर (of_node_test_and_set_flag(nc, OF_POPULATED))
			जारी;
		dev = of_रेजिस्टर_moxtet_device(moxtet, nc);
		अगर (IS_ERR(dev)) अणु
			dev_warn(moxtet->dev,
				 "Failed to create Moxtet device for %pOF\n",
				 nc);
			of_node_clear_flag(nc, OF_POPULATED);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
moxtet_रेजिस्टर_devices_from_topology(काष्ठा moxtet *moxtet)
अणु
	काष्ठा moxtet_device *dev;
	पूर्णांक i, ret;

	क्रम (i = 0; i < moxtet->count; ++i) अणु
		dev = moxtet_alloc_device(moxtet);
		अगर (!dev) अणु
			dev_err(moxtet->dev, "Moxtet device %u alloc error\n",
				i);
			जारी;
		पूर्ण

		dev->idx = i;
		dev->id = moxtet->modules[i];

		ret = moxtet_add_device(dev);
		अगर (ret && ret != -EBUSY) अणु
			put_device(&dev->dev);
			dev_err(moxtet->dev,
				"Moxtet device %u register error: %i\n", i,
				ret);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * @nsame:	how many modules with same id are alपढ़ोy in moxtet->modules
 */
अटल पूर्णांक moxtet_set_irq(काष्ठा moxtet *moxtet, पूर्णांक idx, पूर्णांक id, पूर्णांक nsame)
अणु
	पूर्णांक i, first;
	काष्ठा moxtet_irqpos *pos;

	first = mox_module_table[id].hwirq_base +
		nsame * mox_module_table[id].nirqs;

	अगर (first + mox_module_table[id].nirqs > MOXTET_NIRQS)
		वापस -EINVAL;

	क्रम (i = 0; i < mox_module_table[id].nirqs; ++i) अणु
		pos = &moxtet->irq.position[first + i];
		pos->idx = idx;
		pos->bit = i;
		moxtet->irq.exists |= BIT(first + i);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक moxtet_find_topology(काष्ठा moxtet *moxtet)
अणु
	u8 buf[TURRIS_MOX_MAX_MODULES];
	पूर्णांक cnts[TURRIS_MOX_MODULE_LAST];
	पूर्णांक i, ret;

	स_रखो(cnts, 0, माप(cnts));

	ret = spi_पढ़ो(to_spi_device(moxtet->dev), buf, TURRIS_MOX_MAX_MODULES);
	अगर (ret < 0)
		वापस ret;

	अगर (buf[0] == TURRIS_MOX_CPU_ID_EMMC) अणु
		dev_info(moxtet->dev, "Found MOX A (eMMC CPU) module\n");
	पूर्ण अन्यथा अगर (buf[0] == TURRIS_MOX_CPU_ID_SD) अणु
		dev_info(moxtet->dev, "Found MOX A (CPU) module\n");
	पूर्ण अन्यथा अणु
		dev_err(moxtet->dev, "Invalid Turris MOX A CPU module 0x%02x\n",
			buf[0]);
		वापस -ENODEV;
	पूर्ण

	moxtet->count = 0;

	क्रम (i = 1; i < TURRIS_MOX_MAX_MODULES; ++i) अणु
		पूर्णांक id;

		अगर (buf[i] == 0xff)
			अवरोध;

		id = buf[i] & 0xf;

		moxtet->modules[i-1] = id;
		++moxtet->count;

		अगर (mox_module_known(id)) अणु
			dev_info(moxtet->dev, "Found %s module\n",
				 mox_module_table[id].desc);

			अगर (moxtet_set_irq(moxtet, i-1, id, cnts[id]++) < 0)
				dev_err(moxtet->dev,
					"  Cannot set IRQ for module %s\n",
					mox_module_table[id].desc);
		पूर्ण अन्यथा अणु
			dev_warn(moxtet->dev,
				 "Unknown Moxtet module found (ID 0x%02x)\n",
				 id);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक moxtet_spi_पढ़ो(काष्ठा moxtet *moxtet, u8 *buf)
अणु
	काष्ठा spi_transfer xfer = अणु
		.rx_buf = buf,
		.tx_buf = moxtet->tx,
		.len = moxtet->count + 1
	पूर्ण;
	पूर्णांक ret;

	mutex_lock(&moxtet->lock);

	ret = spi_sync_transfer(to_spi_device(moxtet->dev), &xfer, 1);

	mutex_unlock(&moxtet->lock);

	वापस ret;
पूर्ण

पूर्णांक moxtet_device_पढ़ो(काष्ठा device *dev)
अणु
	काष्ठा moxtet_device *mdev = to_moxtet_device(dev);
	काष्ठा moxtet *moxtet = mdev->moxtet;
	u8 buf[TURRIS_MOX_MAX_MODULES];
	पूर्णांक ret;

	अगर (mdev->idx >= moxtet->count)
		वापस -EINVAL;

	ret = moxtet_spi_पढ़ो(moxtet, buf);
	अगर (ret < 0)
		वापस ret;

	वापस buf[mdev->idx + 1] >> 4;
पूर्ण
EXPORT_SYMBOL_GPL(moxtet_device_पढ़ो);

पूर्णांक moxtet_device_ग_लिखो(काष्ठा device *dev, u8 val)
अणु
	काष्ठा moxtet_device *mdev = to_moxtet_device(dev);
	काष्ठा moxtet *moxtet = mdev->moxtet;
	पूर्णांक ret;

	अगर (mdev->idx >= moxtet->count)
		वापस -EINVAL;

	mutex_lock(&moxtet->lock);

	moxtet->tx[moxtet->count - mdev->idx] = val;

	ret = spi_ग_लिखो(to_spi_device(moxtet->dev), moxtet->tx,
			moxtet->count + 1);

	mutex_unlock(&moxtet->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(moxtet_device_ग_लिखो);

पूर्णांक moxtet_device_written(काष्ठा device *dev)
अणु
	काष्ठा moxtet_device *mdev = to_moxtet_device(dev);
	काष्ठा moxtet *moxtet = mdev->moxtet;

	अगर (mdev->idx >= moxtet->count)
		वापस -EINVAL;

	वापस moxtet->tx[moxtet->count - mdev->idx];
पूर्ण
EXPORT_SYMBOL_GPL(moxtet_device_written);

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक moxtet_debug_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	file->निजी_data = inode->i_निजी;

	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल sमाप_प्रकार input_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार len,
			  loff_t *ppos)
अणु
	काष्ठा moxtet *moxtet = file->निजी_data;
	u8 bin[TURRIS_MOX_MAX_MODULES];
	u8 hex[माप(bin) * 2 + 1];
	पूर्णांक ret, n;

	ret = moxtet_spi_पढ़ो(moxtet, bin);
	अगर (ret < 0)
		वापस ret;

	n = moxtet->count + 1;
	bin2hex(hex, bin, n);

	hex[2*n] = '\n';

	वापस simple_पढ़ो_from_buffer(buf, len, ppos, hex, 2*n + 1);
पूर्ण

अटल स्थिर काष्ठा file_operations input_fops = अणु
	.owner	= THIS_MODULE,
	.खोलो	= moxtet_debug_खोलो,
	.पढ़ो	= input_पढ़ो,
	.llseek	= no_llseek,
पूर्ण;

अटल sमाप_प्रकार output_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार len,
			   loff_t *ppos)
अणु
	काष्ठा moxtet *moxtet = file->निजी_data;
	u8 hex[TURRIS_MOX_MAX_MODULES * 2 + 1];
	u8 *p = hex;
	पूर्णांक i;

	mutex_lock(&moxtet->lock);

	क्रम (i = 0; i < moxtet->count; ++i)
		p = hex_byte_pack(p, moxtet->tx[moxtet->count - i]);

	mutex_unlock(&moxtet->lock);

	*p++ = '\n';

	वापस simple_पढ़ो_from_buffer(buf, len, ppos, hex, p - hex);
पूर्ण

अटल sमाप_प्रकार output_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			    माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा moxtet *moxtet = file->निजी_data;
	u8 bin[TURRIS_MOX_MAX_MODULES];
	u8 hex[माप(bin) * 2 + 1];
	sमाप_प्रकार res;
	loff_t dummy = 0;
	पूर्णांक err, i;

	अगर (len > 2 * moxtet->count + 1 || len < 2 * moxtet->count)
		वापस -EINVAL;

	res = simple_ग_लिखो_to_buffer(hex, माप(hex), &dummy, buf, len);
	अगर (res < 0)
		वापस res;

	अगर (len % 2 == 1 && hex[len - 1] != '\n')
		वापस -EINVAL;

	err = hex2bin(bin, hex, moxtet->count);
	अगर (err < 0)
		वापस -EINVAL;

	mutex_lock(&moxtet->lock);

	क्रम (i = 0; i < moxtet->count; ++i)
		moxtet->tx[moxtet->count - i] = bin[i];

	err = spi_ग_लिखो(to_spi_device(moxtet->dev), moxtet->tx,
			moxtet->count + 1);

	mutex_unlock(&moxtet->lock);

	वापस err < 0 ? err : len;
पूर्ण

अटल स्थिर काष्ठा file_operations output_fops = अणु
	.owner	= THIS_MODULE,
	.खोलो	= moxtet_debug_खोलो,
	.पढ़ो	= output_पढ़ो,
	.ग_लिखो	= output_ग_लिखो,
	.llseek	= no_llseek,
पूर्ण;

अटल पूर्णांक moxtet_रेजिस्टर_debugfs(काष्ठा moxtet *moxtet)
अणु
	काष्ठा dentry *root, *entry;

	root = debugfs_create_dir("moxtet", शून्य);

	अगर (IS_ERR(root))
		वापस PTR_ERR(root);

	entry = debugfs_create_file_unsafe("input", 0444, root, moxtet,
					   &input_fops);
	अगर (IS_ERR(entry))
		जाओ err_हटाओ;

	entry = debugfs_create_file_unsafe("output", 0644, root, moxtet,
					   &output_fops);
	अगर (IS_ERR(entry))
		जाओ err_हटाओ;

	moxtet->debugfs_root = root;

	वापस 0;
err_हटाओ:
	debugfs_हटाओ_recursive(root);
	वापस PTR_ERR(entry);
पूर्ण

अटल व्योम moxtet_unरेजिस्टर_debugfs(काष्ठा moxtet *moxtet)
अणु
	debugfs_हटाओ_recursive(moxtet->debugfs_root);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक moxtet_रेजिस्टर_debugfs(काष्ठा moxtet *moxtet)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम moxtet_unरेजिस्टर_debugfs(काष्ठा moxtet *moxtet)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक moxtet_irq_करोमुख्य_map(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq,
				 irq_hw_number_t hw)
अणु
	काष्ठा moxtet *moxtet = d->host_data;

	अगर (hw >= MOXTET_NIRQS || !(moxtet->irq.exists & BIT(hw))) अणु
		dev_err(moxtet->dev, "Invalid hw irq number\n");
		वापस -EINVAL;
	पूर्ण

	irq_set_chip_data(irq, d->host_data);
	irq_set_chip_and_handler(irq, &moxtet->irq.chip, handle_level_irq);

	वापस 0;
पूर्ण

अटल पूर्णांक moxtet_irq_करोमुख्य_xlate(काष्ठा irq_करोमुख्य *d,
				   काष्ठा device_node *ctrlr,
				   स्थिर u32 *पूर्णांकspec, अचिन्हित पूर्णांक पूर्णांकsize,
				   अचिन्हित दीर्घ *out_hwirq,
				   अचिन्हित पूर्णांक *out_type)
अणु
	काष्ठा moxtet *moxtet = d->host_data;
	पूर्णांक irq;

	अगर (WARN_ON(पूर्णांकsize < 1))
		वापस -EINVAL;

	irq = पूर्णांकspec[0];

	अगर (irq >= MOXTET_NIRQS || !(moxtet->irq.exists & BIT(irq)))
		वापस -EINVAL;

	*out_hwirq = irq;
	*out_type = IRQ_TYPE_NONE;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops moxtet_irq_करोमुख्य = अणु
	.map = moxtet_irq_करोमुख्य_map,
	.xlate = moxtet_irq_करोमुख्य_xlate,
पूर्ण;

अटल व्योम moxtet_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा moxtet *moxtet = irq_data_get_irq_chip_data(d);

	moxtet->irq.masked |= BIT(d->hwirq);
पूर्ण

अटल व्योम moxtet_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा moxtet *moxtet = irq_data_get_irq_chip_data(d);

	moxtet->irq.masked &= ~BIT(d->hwirq);
पूर्ण

अटल व्योम moxtet_irq_prपूर्णांक_chip(काष्ठा irq_data *d, काष्ठा seq_file *p)
अणु
	काष्ठा moxtet *moxtet = irq_data_get_irq_chip_data(d);
	काष्ठा moxtet_irqpos *pos = &moxtet->irq.position[d->hwirq];
	पूर्णांक id;

	id = moxtet->modules[pos->idx];

	seq_म_लिखो(p, " moxtet-%s.%i#%i", mox_module_name(id), pos->idx,
		   pos->bit);
पूर्ण

अटल स्थिर काष्ठा irq_chip moxtet_irq_chip = अणु
	.name			= "moxtet",
	.irq_mask		= moxtet_irq_mask,
	.irq_unmask		= moxtet_irq_unmask,
	.irq_prपूर्णांक_chip		= moxtet_irq_prपूर्णांक_chip,
पूर्ण;

अटल पूर्णांक moxtet_irq_पढ़ो(काष्ठा moxtet *moxtet, अचिन्हित दीर्घ *map)
अणु
	काष्ठा moxtet_irqpos *pos = moxtet->irq.position;
	u8 buf[TURRIS_MOX_MAX_MODULES];
	पूर्णांक i, ret;

	ret = moxtet_spi_पढ़ो(moxtet, buf);
	अगर (ret < 0)
		वापस ret;

	*map = 0;

	क्रम_each_set_bit(i, &moxtet->irq.exists, MOXTET_NIRQS) अणु
		अगर (!(buf[pos[i].idx + 1] & BIT(4 + pos[i].bit)))
			set_bit(i, map);
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t moxtet_irq_thपढ़ो_fn(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा moxtet *moxtet = data;
	अचिन्हित दीर्घ set;
	पूर्णांक nhandled = 0, i, sub_irq, ret;

	ret = moxtet_irq_पढ़ो(moxtet, &set);
	अगर (ret < 0)
		जाओ out;

	set &= ~moxtet->irq.masked;

	करो अणु
		क्रम_each_set_bit(i, &set, MOXTET_NIRQS) अणु
			sub_irq = irq_find_mapping(moxtet->irq.करोमुख्य, i);
			handle_nested_irq(sub_irq);
			dev_dbg(moxtet->dev, "%i irq\n", i);
			++nhandled;
		पूर्ण

		ret = moxtet_irq_पढ़ो(moxtet, &set);
		अगर (ret < 0)
			जाओ out;

		set &= ~moxtet->irq.masked;
	पूर्ण जबतक (set);

out:
	वापस (nhandled > 0 ? IRQ_HANDLED : IRQ_NONE);
पूर्ण

अटल व्योम moxtet_irq_मुक्त(काष्ठा moxtet *moxtet)
अणु
	पूर्णांक i, irq;

	क्रम (i = 0; i < MOXTET_NIRQS; ++i) अणु
		अगर (moxtet->irq.exists & BIT(i)) अणु
			irq = irq_find_mapping(moxtet->irq.करोमुख्य, i);
			irq_dispose_mapping(irq);
		पूर्ण
	पूर्ण

	irq_करोमुख्य_हटाओ(moxtet->irq.करोमुख्य);
पूर्ण

अटल पूर्णांक moxtet_irq_setup(काष्ठा moxtet *moxtet)
अणु
	पूर्णांक i, ret;

	moxtet->irq.करोमुख्य = irq_करोमुख्य_add_simple(moxtet->dev->of_node,
						   MOXTET_NIRQS, 0,
						   &moxtet_irq_करोमुख्य, moxtet);
	अगर (moxtet->irq.करोमुख्य == शून्य) अणु
		dev_err(moxtet->dev, "Could not add IRQ domain\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < MOXTET_NIRQS; ++i)
		अगर (moxtet->irq.exists & BIT(i))
			irq_create_mapping(moxtet->irq.करोमुख्य, i);

	moxtet->irq.chip = moxtet_irq_chip;
	moxtet->irq.masked = ~0;

	ret = request_thपढ़ोed_irq(moxtet->dev_irq, शून्य, moxtet_irq_thपढ़ो_fn,
				   IRQF_ONESHOT, "moxtet", moxtet);
	अगर (ret < 0)
		जाओ err_मुक्त;

	वापस 0;

err_मुक्त:
	moxtet_irq_मुक्त(moxtet);
	वापस ret;
पूर्ण

अटल पूर्णांक moxtet_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा moxtet *moxtet;
	पूर्णांक ret;

	ret = spi_setup(spi);
	अगर (ret < 0)
		वापस ret;

	moxtet = devm_kzalloc(&spi->dev, माप(काष्ठा moxtet),
			      GFP_KERNEL);
	अगर (!moxtet)
		वापस -ENOMEM;

	moxtet->dev = &spi->dev;
	spi_set_drvdata(spi, moxtet);

	mutex_init(&moxtet->lock);

	moxtet->dev_irq = of_irq_get(moxtet->dev->of_node, 0);
	अगर (moxtet->dev_irq == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	अगर (moxtet->dev_irq <= 0) अणु
		dev_err(moxtet->dev, "No IRQ resource found\n");
		वापस -ENXIO;
	पूर्ण

	ret = moxtet_find_topology(moxtet);
	अगर (ret < 0)
		वापस ret;

	अगर (moxtet->irq.exists) अणु
		ret = moxtet_irq_setup(moxtet);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	of_रेजिस्टर_moxtet_devices(moxtet);
	moxtet_रेजिस्टर_devices_from_topology(moxtet);

	ret = moxtet_रेजिस्टर_debugfs(moxtet);
	अगर (ret < 0)
		dev_warn(moxtet->dev, "Failed creating debugfs entries: %i\n",
			 ret);

	वापस 0;
पूर्ण

अटल पूर्णांक moxtet_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा moxtet *moxtet = spi_get_drvdata(spi);

	मुक्त_irq(moxtet->dev_irq, moxtet);

	moxtet_irq_मुक्त(moxtet);

	moxtet_unरेजिस्टर_debugfs(moxtet);

	device_क्रम_each_child(moxtet->dev, शून्य, __unरेजिस्टर);

	mutex_destroy(&moxtet->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id moxtet_dt_ids[] = अणु
	अणु .compatible = "cznic,moxtet" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, moxtet_dt_ids);

अटल काष्ठा spi_driver moxtet_spi_driver = अणु
	.driver = अणु
		.name		= "moxtet",
		.of_match_table = moxtet_dt_ids,
	पूर्ण,
	.probe		= moxtet_probe,
	.हटाओ		= moxtet_हटाओ,
पूर्ण;

अटल पूर्णांक __init moxtet_init(व्योम)
अणु
	पूर्णांक ret;

	ret = bus_रेजिस्टर(&moxtet_bus_type);
	अगर (ret < 0) अणु
		pr_err("moxtet bus registration failed: %d\n", ret);
		जाओ error;
	पूर्ण

	ret = spi_रेजिस्टर_driver(&moxtet_spi_driver);
	अगर (ret < 0) अणु
		pr_err("moxtet spi driver registration failed: %d\n", ret);
		जाओ error_bus;
	पूर्ण

	वापस 0;

error_bus:
	bus_unरेजिस्टर(&moxtet_bus_type);
error:
	वापस ret;
पूर्ण
postcore_initcall_sync(moxtet_init);

अटल व्योम __निकास moxtet_निकास(व्योम)
अणु
	spi_unरेजिस्टर_driver(&moxtet_spi_driver);
	bus_unरेजिस्टर(&moxtet_bus_type);
पूर्ण
module_निकास(moxtet_निकास);

MODULE_AUTHOR("Marek Behun <kabel@kernel.org>");
MODULE_DESCRIPTION("CZ.NIC's Turris Mox module configuration bus");
MODULE_LICENSE("GPL v2");
