<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PS3 FLASH ROM Storage Driver
 *
 * Copyright (C) 2007 Sony Computer Entertainment Inc.
 * Copyright 2007 Sony Corp.
 */

#समावेश <linux/fs.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/lv1call.h>
#समावेश <यंत्र/ps3stor.h>


#घोषणा DEVICE_NAME		"ps3flash"

#घोषणा FLASH_BLOCK_SIZE	(256*1024)


काष्ठा ps3flash_निजी अणु
	काष्ठा mutex mutex;	/* Bounce buffer mutex */
	u64 chunk_sectors;
	पूर्णांक tag;		/* Start sector of buffer, -1 अगर invalid */
	bool dirty;
पूर्ण;

अटल काष्ठा ps3_storage_device *ps3flash_dev;

अटल पूर्णांक ps3flash_पढ़ो_ग_लिखो_sectors(काष्ठा ps3_storage_device *dev,
				       u64 start_sector, पूर्णांक ग_लिखो)
अणु
	काष्ठा ps3flash_निजी *priv = ps3_प्रणाली_bus_get_drvdata(&dev->sbd);
	u64 res = ps3stor_पढ़ो_ग_लिखो_sectors(dev, dev->bounce_lpar,
					     start_sector, priv->chunk_sectors,
					     ग_लिखो);
	अगर (res) अणु
		dev_err(&dev->sbd.core, "%s:%u: %s failed 0x%llx\n", __func__,
			__LINE__, ग_लिखो ? "write" : "read", res);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ps3flash_ग_लिखोback(काष्ठा ps3_storage_device *dev)
अणु
	काष्ठा ps3flash_निजी *priv = ps3_प्रणाली_bus_get_drvdata(&dev->sbd);
	पूर्णांक res;

	अगर (!priv->dirty || priv->tag < 0)
		वापस 0;

	res = ps3flash_पढ़ो_ग_लिखो_sectors(dev, priv->tag, 1);
	अगर (res)
		वापस res;

	priv->dirty = false;
	वापस 0;
पूर्ण

अटल पूर्णांक ps3flash_fetch(काष्ठा ps3_storage_device *dev, u64 start_sector)
अणु
	काष्ठा ps3flash_निजी *priv = ps3_प्रणाली_bus_get_drvdata(&dev->sbd);
	पूर्णांक res;

	अगर (start_sector == priv->tag)
		वापस 0;

	res = ps3flash_ग_लिखोback(dev);
	अगर (res)
		वापस res;

	priv->tag = -1;

	res = ps3flash_पढ़ो_ग_लिखो_sectors(dev, start_sector, 0);
	अगर (res)
		वापस res;

	priv->tag = start_sector;
	वापस 0;
पूर्ण

अटल loff_t ps3flash_llseek(काष्ठा file *file, loff_t offset, पूर्णांक origin)
अणु
	काष्ठा ps3_storage_device *dev = ps3flash_dev;
	वापस generic_file_llseek_size(file, offset, origin, MAX_LFS_खाताSIZE,
			dev->regions[dev->region_idx].size*dev->blk_size);
पूर्ण

अटल sमाप_प्रकार ps3flash_पढ़ो(अक्षर __user *userbuf, व्योम *kernelbuf,
			     माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा ps3_storage_device *dev = ps3flash_dev;
	काष्ठा ps3flash_निजी *priv = ps3_प्रणाली_bus_get_drvdata(&dev->sbd);
	u64 size, sector, offset;
	पूर्णांक res;
	माप_प्रकार reमुख्यing, n;
	स्थिर व्योम *src;

	dev_dbg(&dev->sbd.core,
		"%s:%u: Reading %zu bytes at position %lld to U0x%p/K0x%p\n",
		__func__, __LINE__, count, *pos, userbuf, kernelbuf);

	size = dev->regions[dev->region_idx].size*dev->blk_size;
	अगर (*pos >= size || !count)
		वापस 0;

	अगर (*pos + count > size) अणु
		dev_dbg(&dev->sbd.core,
			"%s:%u Truncating count from %zu to %llu\n", __func__,
			__LINE__, count, size - *pos);
		count = size - *pos;
	पूर्ण

	sector = *pos / dev->bounce_size * priv->chunk_sectors;
	offset = *pos % dev->bounce_size;

	reमुख्यing = count;
	करो अणु
		n = min_t(u64, reमुख्यing, dev->bounce_size - offset);
		src = dev->bounce_buf + offset;

		mutex_lock(&priv->mutex);

		res = ps3flash_fetch(dev, sector);
		अगर (res)
			जाओ fail;

		dev_dbg(&dev->sbd.core,
			"%s:%u: copy %lu bytes from 0x%p to U0x%p/K0x%p\n",
			__func__, __LINE__, n, src, userbuf, kernelbuf);
		अगर (userbuf) अणु
			अगर (copy_to_user(userbuf, src, n)) अणु
				res = -EFAULT;
				जाओ fail;
			पूर्ण
			userbuf += n;
		पूर्ण
		अगर (kernelbuf) अणु
			स_नकल(kernelbuf, src, n);
			kernelbuf += n;
		पूर्ण

		mutex_unlock(&priv->mutex);

		*pos += n;
		reमुख्यing -= n;
		sector += priv->chunk_sectors;
		offset = 0;
	पूर्ण जबतक (reमुख्यing > 0);

	वापस count;

fail:
	mutex_unlock(&priv->mutex);
	वापस res;
पूर्ण

अटल sमाप_प्रकार ps3flash_ग_लिखो(स्थिर अक्षर __user *userbuf,
			      स्थिर व्योम *kernelbuf, माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा ps3_storage_device *dev = ps3flash_dev;
	काष्ठा ps3flash_निजी *priv = ps3_प्रणाली_bus_get_drvdata(&dev->sbd);
	u64 size, sector, offset;
	पूर्णांक res = 0;
	माप_प्रकार reमुख्यing, n;
	व्योम *dst;

	dev_dbg(&dev->sbd.core,
		"%s:%u: Writing %zu bytes at position %lld from U0x%p/K0x%p\n",
		__func__, __LINE__, count, *pos, userbuf, kernelbuf);

	size = dev->regions[dev->region_idx].size*dev->blk_size;
	अगर (*pos >= size || !count)
		वापस 0;

	अगर (*pos + count > size) अणु
		dev_dbg(&dev->sbd.core,
			"%s:%u Truncating count from %zu to %llu\n", __func__,
			__LINE__, count, size - *pos);
		count = size - *pos;
	पूर्ण

	sector = *pos / dev->bounce_size * priv->chunk_sectors;
	offset = *pos % dev->bounce_size;

	reमुख्यing = count;
	करो अणु
		n = min_t(u64, reमुख्यing, dev->bounce_size - offset);
		dst = dev->bounce_buf + offset;

		mutex_lock(&priv->mutex);

		अगर (n != dev->bounce_size)
			res = ps3flash_fetch(dev, sector);
		अन्यथा अगर (sector != priv->tag)
			res = ps3flash_ग_लिखोback(dev);
		अगर (res)
			जाओ fail;

		dev_dbg(&dev->sbd.core,
			"%s:%u: copy %lu bytes from U0x%p/K0x%p to 0x%p\n",
			__func__, __LINE__, n, userbuf, kernelbuf, dst);
		अगर (userbuf) अणु
			अगर (copy_from_user(dst, userbuf, n)) अणु
				res = -EFAULT;
				जाओ fail;
			पूर्ण
			userbuf += n;
		पूर्ण
		अगर (kernelbuf) अणु
			स_नकल(dst, kernelbuf, n);
			kernelbuf += n;
		पूर्ण

		priv->tag = sector;
		priv->dirty = true;

		mutex_unlock(&priv->mutex);

		*pos += n;
		reमुख्यing -= n;
		sector += priv->chunk_sectors;
		offset = 0;
	पूर्ण जबतक (reमुख्यing > 0);

	वापस count;

fail:
	mutex_unlock(&priv->mutex);
	वापस res;
पूर्ण

अटल sमाप_प्रकार ps3flash_user_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				  माप_प्रकार count, loff_t *pos)
अणु
	वापस ps3flash_पढ़ो(buf, शून्य, count, pos);
पूर्ण

अटल sमाप_प्रकार ps3flash_user_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				   माप_प्रकार count, loff_t *pos)
अणु
	वापस ps3flash_ग_लिखो(buf, शून्य, count, pos);
पूर्ण

अटल sमाप_प्रकार ps3flash_kernel_पढ़ो(व्योम *buf, माप_प्रकार count, loff_t pos)
अणु
	वापस ps3flash_पढ़ो(शून्य, buf, count, &pos);
पूर्ण

अटल sमाप_प्रकार ps3flash_kernel_ग_लिखो(स्थिर व्योम *buf, माप_प्रकार count,
				     loff_t pos)
अणु
	sमाप_प्रकार res;
	पूर्णांक wb;

	res = ps3flash_ग_लिखो(शून्य, buf, count, &pos);
	अगर (res < 0)
		वापस res;

	/* Make kernel ग_लिखोs synchronous */
	wb = ps3flash_ग_लिखोback(ps3flash_dev);
	अगर (wb)
		वापस wb;

	वापस res;
पूर्ण

अटल पूर्णांक ps3flash_flush(काष्ठा file *file, fl_owner_t id)
अणु
	वापस ps3flash_ग_लिखोback(ps3flash_dev);
पूर्ण

अटल पूर्णांक ps3flash_fsync(काष्ठा file *file, loff_t start, loff_t end, पूर्णांक datasync)
अणु
	काष्ठा inode *inode = file_inode(file);
	पूर्णांक err;
	inode_lock(inode);
	err = ps3flash_ग_लिखोback(ps3flash_dev);
	inode_unlock(inode);
	वापस err;
पूर्ण

अटल irqवापस_t ps3flash_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ps3_storage_device *dev = data;
	पूर्णांक res;
	u64 tag, status;

	res = lv1_storage_get_async_status(dev->sbd.dev_id, &tag, &status);

	अगर (tag != dev->tag)
		dev_err(&dev->sbd.core,
			"%s:%u: tag mismatch, got %llx, expected %llx\n",
			__func__, __LINE__, tag, dev->tag);

	अगर (res) अणु
		dev_err(&dev->sbd.core, "%s:%u: res=%d status=0x%llx\n",
			__func__, __LINE__, res, status);
	पूर्ण अन्यथा अणु
		dev->lv1_status = status;
		complete(&dev->करोne);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा file_operations ps3flash_fops = अणु
	.owner	= THIS_MODULE,
	.llseek	= ps3flash_llseek,
	.पढ़ो	= ps3flash_user_पढ़ो,
	.ग_लिखो	= ps3flash_user_ग_लिखो,
	.flush	= ps3flash_flush,
	.fsync	= ps3flash_fsync,
पूर्ण;

अटल स्थिर काष्ठा ps3_os_area_flash_ops ps3flash_kernel_ops = अणु
	.पढ़ो	= ps3flash_kernel_पढ़ो,
	.ग_लिखो	= ps3flash_kernel_ग_लिखो,
पूर्ण;

अटल काष्ठा miscdevice ps3flash_misc = अणु
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= DEVICE_NAME,
	.fops	= &ps3flash_fops,
पूर्ण;

अटल पूर्णांक ps3flash_probe(काष्ठा ps3_प्रणाली_bus_device *_dev)
अणु
	काष्ठा ps3_storage_device *dev = to_ps3_storage_device(&_dev->core);
	काष्ठा ps3flash_निजी *priv;
	पूर्णांक error;
	अचिन्हित दीर्घ पंचांगp;

	पंचांगp = dev->regions[dev->region_idx].start*dev->blk_size;
	अगर (पंचांगp % FLASH_BLOCK_SIZE) अणु
		dev_err(&dev->sbd.core,
			"%s:%u region start %lu is not aligned\n", __func__,
			__LINE__, पंचांगp);
		वापस -EINVAL;
	पूर्ण
	पंचांगp = dev->regions[dev->region_idx].size*dev->blk_size;
	अगर (पंचांगp % FLASH_BLOCK_SIZE) अणु
		dev_err(&dev->sbd.core,
			"%s:%u region size %lu is not aligned\n", __func__,
			__LINE__, पंचांगp);
		वापस -EINVAL;
	पूर्ण

	/* use अटल buffer, kदो_स्मृति cannot allocate 256 KiB */
	अगर (!ps3flash_bounce_buffer.address)
		वापस -ENODEV;

	अगर (ps3flash_dev) अणु
		dev_err(&dev->sbd.core,
			"Only one FLASH device is supported\n");
		वापस -EBUSY;
	पूर्ण

	ps3flash_dev = dev;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		error = -ENOMEM;
		जाओ fail;
	पूर्ण

	ps3_प्रणाली_bus_set_drvdata(&dev->sbd, priv);
	mutex_init(&priv->mutex);
	priv->tag = -1;

	dev->bounce_size = ps3flash_bounce_buffer.size;
	dev->bounce_buf = ps3flash_bounce_buffer.address;
	priv->chunk_sectors = dev->bounce_size / dev->blk_size;

	error = ps3stor_setup(dev, ps3flash_पूर्णांकerrupt);
	अगर (error)
		जाओ fail_मुक्त_priv;

	ps3flash_misc.parent = &dev->sbd.core;
	error = misc_रेजिस्टर(&ps3flash_misc);
	अगर (error) अणु
		dev_err(&dev->sbd.core, "%s:%u: misc_register failed %d\n",
			__func__, __LINE__, error);
		जाओ fail_tearकरोwn;
	पूर्ण

	dev_info(&dev->sbd.core, "%s:%u: registered misc device %d\n",
		 __func__, __LINE__, ps3flash_misc.minor);

	ps3_os_area_flash_रेजिस्टर(&ps3flash_kernel_ops);
	वापस 0;

fail_tearकरोwn:
	ps3stor_tearकरोwn(dev);
fail_मुक्त_priv:
	kमुक्त(priv);
	ps3_प्रणाली_bus_set_drvdata(&dev->sbd, शून्य);
fail:
	ps3flash_dev = शून्य;
	वापस error;
पूर्ण

अटल व्योम ps3flash_हटाओ(काष्ठा ps3_प्रणाली_bus_device *_dev)
अणु
	काष्ठा ps3_storage_device *dev = to_ps3_storage_device(&_dev->core);

	ps3_os_area_flash_रेजिस्टर(शून्य);
	misc_deरेजिस्टर(&ps3flash_misc);
	ps3stor_tearकरोwn(dev);
	kमुक्त(ps3_प्रणाली_bus_get_drvdata(&dev->sbd));
	ps3_प्रणाली_bus_set_drvdata(&dev->sbd, शून्य);
	ps3flash_dev = शून्य;
पूर्ण


अटल काष्ठा ps3_प्रणाली_bus_driver ps3flash = अणु
	.match_id	= PS3_MATCH_ID_STOR_FLASH,
	.core.name	= DEVICE_NAME,
	.core.owner	= THIS_MODULE,
	.probe		= ps3flash_probe,
	.हटाओ		= ps3flash_हटाओ,
	.shutकरोwn	= ps3flash_हटाओ,
पूर्ण;


अटल पूर्णांक __init ps3flash_init(व्योम)
अणु
	वापस ps3_प्रणाली_bus_driver_रेजिस्टर(&ps3flash);
पूर्ण

अटल व्योम __निकास ps3flash_निकास(व्योम)
अणु
	ps3_प्रणाली_bus_driver_unरेजिस्टर(&ps3flash);
पूर्ण

module_init(ps3flash_init);
module_निकास(ps3flash_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PS3 FLASH ROM Storage Driver");
MODULE_AUTHOR("Sony Corporation");
MODULE_ALIAS(PS3_MODULE_ALIAS_STOR_FLASH);
