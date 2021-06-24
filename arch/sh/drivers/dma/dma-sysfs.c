<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/drivers/dma/dma-sysfs.c
 *
 * sysfs पूर्णांकerface क्रम SH DMA API
 *
 * Copyright (C) 2004 - 2006  Paul Mundt
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/dma.h>

अटल काष्ठा bus_type dma_subsys = अणु
	.name = "dma",
	.dev_name = "dma",
पूर्ण;

अटल sमाप_प्रकार dma_show_devices(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++) अणु
		काष्ठा dma_info *info = get_dma_info(i);
		काष्ठा dma_channel *channel = get_dma_channel(i);

		अगर (unlikely(!info) || !channel)
			जारी;

		len += प्र_लिखो(buf + len, "%2d: %14s    %s\n",
			       channel->chan, info->name,
			       channel->dev_id);
	पूर्ण

	वापस len;
पूर्ण

अटल DEVICE_ATTR(devices, S_IRUGO, dma_show_devices, शून्य);

अटल पूर्णांक __init dma_subsys_init(व्योम)
अणु
	पूर्णांक ret;

	ret = subsys_प्रणाली_रेजिस्टर(&dma_subsys, शून्य);
	अगर (unlikely(ret))
		वापस ret;

	वापस device_create_file(dma_subsys.dev_root, &dev_attr_devices);
पूर्ण
postcore_initcall(dma_subsys_init);

अटल sमाप_प्रकार dma_show_dev_id(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dma_channel *channel = to_dma_channel(dev);
	वापस प्र_लिखो(buf, "%s\n", channel->dev_id);
पूर्ण

अटल sमाप_प्रकार dma_store_dev_id(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dma_channel *channel = to_dma_channel(dev);
	म_नकल(channel->dev_id, buf);
	वापस count;
पूर्ण

अटल DEVICE_ATTR(dev_id, S_IRUGO | S_IWUSR, dma_show_dev_id, dma_store_dev_id);

अटल sमाप_प्रकार dma_store_config(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dma_channel *channel = to_dma_channel(dev);
	अचिन्हित दीर्घ config;

	config = simple_म_से_अदीर्घ(buf, शून्य, 0);
	dma_configure_channel(channel->vchan, config);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(config, S_IWUSR, शून्य, dma_store_config);

अटल sमाप_प्रकार dma_show_mode(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dma_channel *channel = to_dma_channel(dev);
	वापस प्र_लिखो(buf, "0x%08x\n", channel->mode);
पूर्ण

अटल sमाप_प्रकार dma_store_mode(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा dma_channel *channel = to_dma_channel(dev);
	channel->mode = simple_म_से_अदीर्घ(buf, शून्य, 0);
	वापस count;
पूर्ण

अटल DEVICE_ATTR(mode, S_IRUGO | S_IWUSR, dma_show_mode, dma_store_mode);

#घोषणा dma_ro_attr(field, fmt)						\
अटल sमाप_प्रकार dma_show_##field(काष्ठा device *dev,		\
				काष्ठा device_attribute *attr, अक्षर *buf)\
अणु									\
	काष्ठा dma_channel *channel = to_dma_channel(dev);		\
	वापस प्र_लिखो(buf, fmt, channel->field);			\
पूर्ण									\
अटल DEVICE_ATTR(field, S_IRUGO, dma_show_##field, शून्य);

dma_ro_attr(count, "0x%08x\n");
dma_ro_attr(flags, "0x%08lx\n");

पूर्णांक dma_create_sysfs_files(काष्ठा dma_channel *chan, काष्ठा dma_info *info)
अणु
	काष्ठा device *dev = &chan->dev;
	अक्षर name[16];
	पूर्णांक ret;

	dev->id  = chan->vchan;
	dev->bus = &dma_subsys;

	ret = device_रेजिस्टर(dev);
	अगर (ret)
		वापस ret;

	ret |= device_create_file(dev, &dev_attr_dev_id);
	ret |= device_create_file(dev, &dev_attr_count);
	ret |= device_create_file(dev, &dev_attr_mode);
	ret |= device_create_file(dev, &dev_attr_flags);
	ret |= device_create_file(dev, &dev_attr_config);

	अगर (unlikely(ret)) अणु
		dev_err(&info->pdev->dev, "Failed creating attrs\n");
		वापस ret;
	पूर्ण

	snम_लिखो(name, माप(name), "dma%d", chan->chan);
	वापस sysfs_create_link(&info->pdev->dev.kobj, &dev->kobj, name);
पूर्ण

व्योम dma_हटाओ_sysfs_files(काष्ठा dma_channel *chan, काष्ठा dma_info *info)
अणु
	काष्ठा device *dev = &chan->dev;
	अक्षर name[16];

	device_हटाओ_file(dev, &dev_attr_dev_id);
	device_हटाओ_file(dev, &dev_attr_count);
	device_हटाओ_file(dev, &dev_attr_mode);
	device_हटाओ_file(dev, &dev_attr_flags);
	device_हटाओ_file(dev, &dev_attr_config);

	snम_लिखो(name, माप(name), "dma%d", chan->chan);
	sysfs_हटाओ_link(&info->pdev->dev.kobj, name);

	device_unरेजिस्टर(dev);
पूर्ण
