<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PS3 Disk Storage Driver
 *
 * Copyright (C) 2007 Sony Computer Entertainment Inc.
 * Copyright 2007 Sony Corp.
 */

#समावेश <linux/ata.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/lv1call.h>
#समावेश <यंत्र/ps3stor.h>
#समावेश <यंत्र/firmware.h>


#घोषणा DEVICE_NAME		"ps3disk"

#घोषणा BOUNCE_SIZE		(64*1024)

#घोषणा PS3DISK_MAX_DISKS	16
#घोषणा PS3DISK_MINORS		16


#घोषणा PS3DISK_NAME		"ps3d%c"


काष्ठा ps3disk_निजी अणु
	spinlock_t lock;		/* Request queue spinlock */
	काष्ठा request_queue *queue;
	काष्ठा blk_mq_tag_set tag_set;
	काष्ठा gendisk *gendisk;
	अचिन्हित पूर्णांक blocking_factor;
	काष्ठा request *req;
	u64 raw_capacity;
	अचिन्हित अक्षर model[ATA_ID_PROD_LEN+1];
पूर्ण;


#घोषणा LV1_STORAGE_SEND_ATA_COMMAND	(2)
#घोषणा LV1_STORAGE_ATA_HDDOUT		(0x23)

काष्ठा lv1_ata_cmnd_block अणु
	u16	features;
	u16	sector_count;
	u16	LBA_low;
	u16	LBA_mid;
	u16	LBA_high;
	u8	device;
	u8	command;
	u32	is_ext;
	u32	proto;
	u32	in_out;
	u32	size;
	u64	buffer;
	u32	arglen;
पूर्ण;

क्रमागत lv1_ata_proto अणु
	NON_DATA_PROTO     = 0,
	PIO_DATA_IN_PROTO  = 1,
	PIO_DATA_OUT_PROTO = 2,
	DMA_PROTO = 3
पूर्ण;

क्रमागत lv1_ata_in_out अणु
	सूची_WRITE = 0,			/* memory -> device */
	सूची_READ = 1			/* device -> memory */
पूर्ण;

अटल पूर्णांक ps3disk_major;


अटल स्थिर काष्ठा block_device_operations ps3disk_fops = अणु
	.owner		= THIS_MODULE,
पूर्ण;


अटल व्योम ps3disk_scatter_gather(काष्ठा ps3_storage_device *dev,
				   काष्ठा request *req, पूर्णांक gather)
अणु
	अचिन्हित पूर्णांक offset = 0;
	काष्ठा req_iterator iter;
	काष्ठा bio_vec bvec;
	अचिन्हित पूर्णांक i = 0;
	माप_प्रकार size;
	व्योम *buf;

	rq_क्रम_each_segment(bvec, req, iter) अणु
		अचिन्हित दीर्घ flags;
		dev_dbg(&dev->sbd.core, "%s:%u: bio %u: %u sectors from %llu\n",
			__func__, __LINE__, i, bio_sectors(iter.bio),
			iter.bio->bi_iter.bi_sector);

		size = bvec.bv_len;
		buf = bvec_kmap_irq(&bvec, &flags);
		अगर (gather)
			स_नकल(dev->bounce_buf+offset, buf, size);
		अन्यथा
			स_नकल(buf, dev->bounce_buf+offset, size);
		offset += size;
		flush_kernel_dcache_page(bvec.bv_page);
		bvec_kunmap_irq(buf, &flags);
		i++;
	पूर्ण
पूर्ण

अटल blk_status_t ps3disk_submit_request_sg(काष्ठा ps3_storage_device *dev,
					      काष्ठा request *req)
अणु
	काष्ठा ps3disk_निजी *priv = ps3_प्रणाली_bus_get_drvdata(&dev->sbd);
	पूर्णांक ग_लिखो = rq_data_dir(req), res;
	स्थिर अक्षर *op = ग_लिखो ? "write" : "read";
	u64 start_sector, sectors;
	अचिन्हित पूर्णांक region_id = dev->regions[dev->region_idx].id;

#अगर_घोषित DEBUG
	अचिन्हित पूर्णांक n = 0;
	काष्ठा bio_vec bv;
	काष्ठा req_iterator iter;

	rq_क्रम_each_segment(bv, req, iter)
		n++;
	dev_dbg(&dev->sbd.core,
		"%s:%u: %s req has %u bvecs for %u sectors\n",
		__func__, __LINE__, op, n, blk_rq_sectors(req));
#पूर्ण_अगर

	start_sector = blk_rq_pos(req) * priv->blocking_factor;
	sectors = blk_rq_sectors(req) * priv->blocking_factor;
	dev_dbg(&dev->sbd.core, "%s:%u: %s %llu sectors starting at %llu\n",
		__func__, __LINE__, op, sectors, start_sector);

	अगर (ग_लिखो) अणु
		ps3disk_scatter_gather(dev, req, 1);

		res = lv1_storage_ग_लिखो(dev->sbd.dev_id, region_id,
					start_sector, sectors, 0,
					dev->bounce_lpar, &dev->tag);
	पूर्ण अन्यथा अणु
		res = lv1_storage_पढ़ो(dev->sbd.dev_id, region_id,
				       start_sector, sectors, 0,
				       dev->bounce_lpar, &dev->tag);
	पूर्ण
	अगर (res) अणु
		dev_err(&dev->sbd.core, "%s:%u: %s failed %d\n", __func__,
			__LINE__, op, res);
		वापस BLK_STS_IOERR;
	पूर्ण

	priv->req = req;
	वापस BLK_STS_OK;
पूर्ण

अटल blk_status_t ps3disk_submit_flush_request(काष्ठा ps3_storage_device *dev,
						 काष्ठा request *req)
अणु
	काष्ठा ps3disk_निजी *priv = ps3_प्रणाली_bus_get_drvdata(&dev->sbd);
	u64 res;

	dev_dbg(&dev->sbd.core, "%s:%u: flush request\n", __func__, __LINE__);

	res = lv1_storage_send_device_command(dev->sbd.dev_id,
					      LV1_STORAGE_ATA_HDDOUT, 0, 0, 0,
					      0, &dev->tag);
	अगर (res) अणु
		dev_err(&dev->sbd.core, "%s:%u: sync cache failed 0x%llx\n",
			__func__, __LINE__, res);
		वापस BLK_STS_IOERR;
	पूर्ण

	priv->req = req;
	वापस BLK_STS_OK;
पूर्ण

अटल blk_status_t ps3disk_करो_request(काष्ठा ps3_storage_device *dev,
				       काष्ठा request *req)
अणु
	dev_dbg(&dev->sbd.core, "%s:%u\n", __func__, __LINE__);

	चयन (req_op(req)) अणु
	हाल REQ_OP_FLUSH:
		वापस ps3disk_submit_flush_request(dev, req);
	हाल REQ_OP_READ:
	हाल REQ_OP_WRITE:
		वापस ps3disk_submit_request_sg(dev, req);
	शेष:
		blk_dump_rq_flags(req, DEVICE_NAME " bad request");
		वापस BLK_STS_IOERR;
	पूर्ण
पूर्ण

अटल blk_status_t ps3disk_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				     स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा request_queue *q = hctx->queue;
	काष्ठा ps3_storage_device *dev = q->queuedata;
	काष्ठा ps3disk_निजी *priv = ps3_प्रणाली_bus_get_drvdata(&dev->sbd);
	blk_status_t ret;

	blk_mq_start_request(bd->rq);

	spin_lock_irq(&priv->lock);
	ret = ps3disk_करो_request(dev, bd->rq);
	spin_unlock_irq(&priv->lock);

	वापस ret;
पूर्ण

अटल irqवापस_t ps3disk_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ps3_storage_device *dev = data;
	काष्ठा ps3disk_निजी *priv;
	काष्ठा request *req;
	पूर्णांक res, पढ़ो;
	blk_status_t error;
	u64 tag, status;
	स्थिर अक्षर *op;

	res = lv1_storage_get_async_status(dev->sbd.dev_id, &tag, &status);

	अगर (tag != dev->tag)
		dev_err(&dev->sbd.core,
			"%s:%u: tag mismatch, got %llx, expected %llx\n",
			__func__, __LINE__, tag, dev->tag);

	अगर (res) अणु
		dev_err(&dev->sbd.core, "%s:%u: res=%d status=0x%llx\n",
			__func__, __LINE__, res, status);
		वापस IRQ_HANDLED;
	पूर्ण

	priv = ps3_प्रणाली_bus_get_drvdata(&dev->sbd);
	req = priv->req;
	अगर (!req) अणु
		dev_dbg(&dev->sbd.core,
			"%s:%u non-block layer request completed\n", __func__,
			__LINE__);
		dev->lv1_status = status;
		complete(&dev->करोne);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (req_op(req) == REQ_OP_FLUSH) अणु
		पढ़ो = 0;
		op = "flush";
	पूर्ण अन्यथा अणु
		पढ़ो = !rq_data_dir(req);
		op = पढ़ो ? "read" : "write";
	पूर्ण
	अगर (status) अणु
		dev_dbg(&dev->sbd.core, "%s:%u: %s failed 0x%llx\n", __func__,
			__LINE__, op, status);
		error = BLK_STS_IOERR;
	पूर्ण अन्यथा अणु
		dev_dbg(&dev->sbd.core, "%s:%u: %s completed\n", __func__,
			__LINE__, op);
		error = 0;
		अगर (पढ़ो)
			ps3disk_scatter_gather(dev, req, 0);
	पूर्ण

	spin_lock(&priv->lock);
	priv->req = शून्य;
	blk_mq_end_request(req, error);
	spin_unlock(&priv->lock);

	blk_mq_run_hw_queues(priv->queue, true);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ps3disk_sync_cache(काष्ठा ps3_storage_device *dev)
अणु
	u64 res;

	dev_dbg(&dev->sbd.core, "%s:%u: sync cache\n", __func__, __LINE__);

	res = ps3stor_send_command(dev, LV1_STORAGE_ATA_HDDOUT, 0, 0, 0, 0);
	अगर (res) अणु
		dev_err(&dev->sbd.core, "%s:%u: sync cache failed 0x%llx\n",
			__func__, __LINE__, res);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण


/* ATA helpers copied from drivers/ata/libata-core.c */

अटल व्योम swap_buf_le16(u16 *buf, अचिन्हित पूर्णांक buf_words)
अणु
#अगर_घोषित __BIG_ENDIAN
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < buf_words; i++)
		buf[i] = le16_to_cpu(buf[i]);
#पूर्ण_अगर /* __BIG_ENDIAN */
पूर्ण

अटल u64 ata_id_n_sectors(स्थिर u16 *id)
अणु
	अगर (ata_id_has_lba(id)) अणु
		अगर (ata_id_has_lba48(id))
			वापस ata_id_u64(id, 100);
		अन्यथा
			वापस ata_id_u32(id, 60);
	पूर्ण अन्यथा अणु
		अगर (ata_id_current_chs_valid(id))
			वापस ata_id_u32(id, 57);
		अन्यथा
			वापस id[1] * id[3] * id[6];
	पूर्ण
पूर्ण

अटल व्योम ata_id_string(स्थिर u16 *id, अचिन्हित अक्षर *s, अचिन्हित पूर्णांक ofs,
			  अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक c;

	जबतक (len > 0) अणु
		c = id[ofs] >> 8;
		*s = c;
		s++;

		c = id[ofs] & 0xff;
		*s = c;
		s++;

		ofs++;
		len -= 2;
	पूर्ण
पूर्ण

अटल व्योम ata_id_c_string(स्थिर u16 *id, अचिन्हित अक्षर *s, अचिन्हित पूर्णांक ofs,
			    अचिन्हित पूर्णांक len)
अणु
	अचिन्हित अक्षर *p;

	WARN_ON(!(len & 1));

	ata_id_string(id, s, ofs, len - 1);

	p = s + strnlen(s, len - 1);
	जबतक (p > s && p[-1] == ' ')
		p--;
	*p = '\0';
पूर्ण

अटल पूर्णांक ps3disk_identअगरy(काष्ठा ps3_storage_device *dev)
अणु
	काष्ठा ps3disk_निजी *priv = ps3_प्रणाली_bus_get_drvdata(&dev->sbd);
	काष्ठा lv1_ata_cmnd_block ata_cmnd;
	u16 *id = dev->bounce_buf;
	u64 res;

	dev_dbg(&dev->sbd.core, "%s:%u: identify disk\n", __func__, __LINE__);

	स_रखो(&ata_cmnd, 0, माप(काष्ठा lv1_ata_cmnd_block));
	ata_cmnd.command = ATA_CMD_ID_ATA;
	ata_cmnd.sector_count = 1;
	ata_cmnd.size = ata_cmnd.arglen = ATA_ID_WORDS * 2;
	ata_cmnd.buffer = dev->bounce_lpar;
	ata_cmnd.proto = PIO_DATA_IN_PROTO;
	ata_cmnd.in_out = सूची_READ;

	res = ps3stor_send_command(dev, LV1_STORAGE_SEND_ATA_COMMAND,
				   ps3_mm_phys_to_lpar(__pa(&ata_cmnd)),
				   माप(ata_cmnd), ata_cmnd.buffer,
				   ata_cmnd.arglen);
	अगर (res) अणु
		dev_err(&dev->sbd.core, "%s:%u: identify disk failed 0x%llx\n",
			__func__, __LINE__, res);
		वापस -EIO;
	पूर्ण

	swap_buf_le16(id, ATA_ID_WORDS);

	/* All we're पूर्णांकerested in are raw capacity and model name */
	priv->raw_capacity = ata_id_n_sectors(id);
	ata_id_c_string(id, priv->model, ATA_ID_PROD, माप(priv->model));
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ ps3disk_mask;

अटल DEFINE_MUTEX(ps3disk_mask_mutex);

अटल स्थिर काष्ठा blk_mq_ops ps3disk_mq_ops = अणु
	.queue_rq	= ps3disk_queue_rq,
पूर्ण;

अटल पूर्णांक ps3disk_probe(काष्ठा ps3_प्रणाली_bus_device *_dev)
अणु
	काष्ठा ps3_storage_device *dev = to_ps3_storage_device(&_dev->core);
	काष्ठा ps3disk_निजी *priv;
	पूर्णांक error;
	अचिन्हित पूर्णांक devidx;
	काष्ठा request_queue *queue;
	काष्ठा gendisk *gendisk;

	अगर (dev->blk_size < 512) अणु
		dev_err(&dev->sbd.core,
			"%s:%u: cannot handle block size %llu\n", __func__,
			__LINE__, dev->blk_size);
		वापस -EINVAL;
	पूर्ण

	BUILD_BUG_ON(PS3DISK_MAX_DISKS > BITS_PER_LONG);
	mutex_lock(&ps3disk_mask_mutex);
	devidx = find_first_zero_bit(&ps3disk_mask, PS3DISK_MAX_DISKS);
	अगर (devidx >= PS3DISK_MAX_DISKS) अणु
		dev_err(&dev->sbd.core, "%s:%u: Too many disks\n", __func__,
			__LINE__);
		mutex_unlock(&ps3disk_mask_mutex);
		वापस -ENOSPC;
	पूर्ण
	__set_bit(devidx, &ps3disk_mask);
	mutex_unlock(&ps3disk_mask_mutex);

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv) अणु
		error = -ENOMEM;
		जाओ fail;
	पूर्ण

	ps3_प्रणाली_bus_set_drvdata(_dev, priv);
	spin_lock_init(&priv->lock);

	dev->bounce_size = BOUNCE_SIZE;
	dev->bounce_buf = kदो_स्मृति(BOUNCE_SIZE, GFP_DMA);
	अगर (!dev->bounce_buf) अणु
		error = -ENOMEM;
		जाओ fail_मुक्त_priv;
	पूर्ण

	error = ps3stor_setup(dev, ps3disk_पूर्णांकerrupt);
	अगर (error)
		जाओ fail_मुक्त_bounce;

	ps3disk_identअगरy(dev);

	queue = blk_mq_init_sq_queue(&priv->tag_set, &ps3disk_mq_ops, 1,
					BLK_MQ_F_SHOULD_MERGE);
	अगर (IS_ERR(queue)) अणु
		dev_err(&dev->sbd.core, "%s:%u: blk_mq_init_queue failed\n",
			__func__, __LINE__);
		error = PTR_ERR(queue);
		जाओ fail_tearकरोwn;
	पूर्ण

	priv->queue = queue;
	queue->queuedata = dev;

	blk_queue_max_hw_sectors(queue, dev->bounce_size >> 9);
	blk_queue_dma_alignment(queue, dev->blk_size-1);
	blk_queue_logical_block_size(queue, dev->blk_size);

	blk_queue_ग_लिखो_cache(queue, true, false);

	blk_queue_max_segments(queue, -1);
	blk_queue_max_segment_size(queue, dev->bounce_size);

	gendisk = alloc_disk(PS3DISK_MINORS);
	अगर (!gendisk) अणु
		dev_err(&dev->sbd.core, "%s:%u: alloc_disk failed\n", __func__,
			__LINE__);
		error = -ENOMEM;
		जाओ fail_cleanup_queue;
	पूर्ण

	priv->gendisk = gendisk;
	gendisk->major = ps3disk_major;
	gendisk->first_minor = devidx * PS3DISK_MINORS;
	gendisk->fops = &ps3disk_fops;
	gendisk->queue = queue;
	gendisk->निजी_data = dev;
	snम_लिखो(gendisk->disk_name, माप(gendisk->disk_name), PS3DISK_NAME,
		 devidx+'a');
	priv->blocking_factor = dev->blk_size >> 9;
	set_capacity(gendisk,
		     dev->regions[dev->region_idx].size*priv->blocking_factor);

	dev_info(&dev->sbd.core,
		 "%s is a %s (%llu MiB total, %llu MiB for OtherOS)\n",
		 gendisk->disk_name, priv->model, priv->raw_capacity >> 11,
		 get_capacity(gendisk) >> 11);

	device_add_disk(&dev->sbd.core, gendisk, शून्य);
	वापस 0;

fail_cleanup_queue:
	blk_cleanup_queue(queue);
	blk_mq_मुक्त_tag_set(&priv->tag_set);
fail_tearकरोwn:
	ps3stor_tearकरोwn(dev);
fail_मुक्त_bounce:
	kमुक्त(dev->bounce_buf);
fail_मुक्त_priv:
	kमुक्त(priv);
	ps3_प्रणाली_bus_set_drvdata(_dev, शून्य);
fail:
	mutex_lock(&ps3disk_mask_mutex);
	__clear_bit(devidx, &ps3disk_mask);
	mutex_unlock(&ps3disk_mask_mutex);
	वापस error;
पूर्ण

अटल व्योम ps3disk_हटाओ(काष्ठा ps3_प्रणाली_bus_device *_dev)
अणु
	काष्ठा ps3_storage_device *dev = to_ps3_storage_device(&_dev->core);
	काष्ठा ps3disk_निजी *priv = ps3_प्रणाली_bus_get_drvdata(&dev->sbd);

	mutex_lock(&ps3disk_mask_mutex);
	__clear_bit(MINOR(disk_devt(priv->gendisk)) / PS3DISK_MINORS,
		    &ps3disk_mask);
	mutex_unlock(&ps3disk_mask_mutex);
	del_gendisk(priv->gendisk);
	blk_cleanup_queue(priv->queue);
	blk_mq_मुक्त_tag_set(&priv->tag_set);
	put_disk(priv->gendisk);
	dev_notice(&dev->sbd.core, "Synchronizing disk cache\n");
	ps3disk_sync_cache(dev);
	ps3stor_tearकरोwn(dev);
	kमुक्त(dev->bounce_buf);
	kमुक्त(priv);
	ps3_प्रणाली_bus_set_drvdata(_dev, शून्य);
पूर्ण

अटल काष्ठा ps3_प्रणाली_bus_driver ps3disk = अणु
	.match_id	= PS3_MATCH_ID_STOR_DISK,
	.core.name	= DEVICE_NAME,
	.core.owner	= THIS_MODULE,
	.probe		= ps3disk_probe,
	.हटाओ		= ps3disk_हटाओ,
	.shutकरोwn	= ps3disk_हटाओ,
पूर्ण;


अटल पूर्णांक __init ps3disk_init(व्योम)
अणु
	पूर्णांक error;

	अगर (!firmware_has_feature(FW_FEATURE_PS3_LV1))
		वापस -ENODEV;

	error = रेजिस्टर_blkdev(0, DEVICE_NAME);
	अगर (error <= 0) अणु
		prपूर्णांकk(KERN_ERR "%s:%u: register_blkdev failed %d\n", __func__,
		       __LINE__, error);
		वापस error;
	पूर्ण
	ps3disk_major = error;

	pr_info("%s:%u: registered block device major %d\n", __func__,
		__LINE__, ps3disk_major);

	error = ps3_प्रणाली_bus_driver_रेजिस्टर(&ps3disk);
	अगर (error)
		unरेजिस्टर_blkdev(ps3disk_major, DEVICE_NAME);

	वापस error;
पूर्ण

अटल व्योम __निकास ps3disk_निकास(व्योम)
अणु
	ps3_प्रणाली_bus_driver_unरेजिस्टर(&ps3disk);
	unरेजिस्टर_blkdev(ps3disk_major, DEVICE_NAME);
पूर्ण

module_init(ps3disk_init);
module_निकास(ps3disk_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PS3 Disk Storage Driver");
MODULE_AUTHOR("Sony Corporation");
MODULE_ALIAS(PS3_MODULE_ALIAS_STOR_DISK);
