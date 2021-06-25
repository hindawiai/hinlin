<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 Ezequiel Garcia
 * Copyright (c) 2011 Free Electrons
 *
 * Driver parameter handling strongly based on drivers/mtd/ubi/build.c
 *   Copyright (c) International Business Machines Corp., 2006
 *   Copyright (c) Nokia Corporation, 2007
 *   Authors: Artem Bityutskiy, Frank Haverkamp
 */

/*
 * Read-only block devices on top of UBI volumes
 *
 * A simple implementation to allow a block device to be layered on top of a
 * UBI volume. The implementation is provided by creating a अटल 1-to-1
 * mapping between the block device and the UBI volume.
 *
 * The addressed byte is obtained from the addressed block sector, which is
 * mapped linearly पूर्णांकo the corresponding LEB:
 *
 *   LEB number = addressed byte / LEB size
 *
 * This feature is compiled in the UBI core, and adds a 'block' parameter
 * to allow early creation of block devices on top of UBI volumes. Runसमय
 * block creation/removal क्रम UBI volumes is provided through two UBI ioctls:
 * UBI_IOCVOLCRBLK and UBI_IOCVOLRMBLK.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/ubi.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/idr.h>
#समावेश <यंत्र/भाग64.h>

#समावेश "ubi-media.h"
#समावेश "ubi.h"

/* Maximum number of supported devices */
#घोषणा UBIBLOCK_MAX_DEVICES 32

/* Maximum length of the 'block=' parameter */
#घोषणा UBIBLOCK_PARAM_LEN 63

/* Maximum number of comma-separated items in the 'block=' parameter */
#घोषणा UBIBLOCK_PARAM_COUNT 2

काष्ठा ubiblock_param अणु
	पूर्णांक ubi_num;
	पूर्णांक vol_id;
	अक्षर name[UBIBLOCK_PARAM_LEN+1];
पूर्ण;

काष्ठा ubiblock_pdu अणु
	काष्ठा work_काष्ठा work;
	काष्ठा ubi_sgl usgl;
पूर्ण;

/* Numbers of elements set in the @ubiblock_param array */
अटल पूर्णांक ubiblock_devs __initdata;

/* MTD devices specअगरication parameters */
अटल काष्ठा ubiblock_param ubiblock_param[UBIBLOCK_MAX_DEVICES] __initdata;

काष्ठा ubiblock अणु
	काष्ठा ubi_volume_desc *desc;
	पूर्णांक ubi_num;
	पूर्णांक vol_id;
	पूर्णांक refcnt;
	पूर्णांक leb_size;

	काष्ठा gendisk *gd;
	काष्ठा request_queue *rq;

	काष्ठा workqueue_काष्ठा *wq;

	काष्ठा mutex dev_mutex;
	काष्ठा list_head list;
	काष्ठा blk_mq_tag_set tag_set;
पूर्ण;

/* Linked list of all ubiblock instances */
अटल LIST_HEAD(ubiblock_devices);
अटल DEFINE_IDR(ubiblock_minor_idr);
/* Protects ubiblock_devices and ubiblock_minor_idr */
अटल DEFINE_MUTEX(devices_mutex);
अटल पूर्णांक ubiblock_major;

अटल पूर्णांक __init ubiblock_set_param(स्थिर अक्षर *val,
				     स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक i, ret;
	माप_प्रकार len;
	काष्ठा ubiblock_param *param;
	अक्षर buf[UBIBLOCK_PARAM_LEN];
	अक्षर *pbuf = &buf[0];
	अक्षर *tokens[UBIBLOCK_PARAM_COUNT];

	अगर (!val)
		वापस -EINVAL;

	len = strnlen(val, UBIBLOCK_PARAM_LEN);
	अगर (len == 0) अणु
		pr_warn("UBI: block: empty 'block=' parameter - ignored\n");
		वापस 0;
	पूर्ण

	अगर (len == UBIBLOCK_PARAM_LEN) अणु
		pr_err("UBI: block: parameter \"%s\" is too long, max. is %d\n",
		       val, UBIBLOCK_PARAM_LEN);
		वापस -EINVAL;
	पूर्ण

	म_नकल(buf, val);

	/* Get rid of the final newline */
	अगर (buf[len - 1] == '\n')
		buf[len - 1] = '\0';

	क्रम (i = 0; i < UBIBLOCK_PARAM_COUNT; i++)
		tokens[i] = strsep(&pbuf, ",");

	param = &ubiblock_param[ubiblock_devs];
	अगर (tokens[1]) अणु
		/* Two parameters: can be 'ubi, vol_id' or 'ubi, vol_name' */
		ret = kstrtoपूर्णांक(tokens[0], 10, &param->ubi_num);
		अगर (ret < 0)
			वापस -EINVAL;

		/* Second param can be a number or a name */
		ret = kstrtoपूर्णांक(tokens[1], 10, &param->vol_id);
		अगर (ret < 0) अणु
			param->vol_id = -1;
			म_नकल(param->name, tokens[1]);
		पूर्ण

	पूर्ण अन्यथा अणु
		/* One parameter: must be device path */
		म_नकल(param->name, tokens[0]);
		param->ubi_num = -1;
		param->vol_id = -1;
	पूर्ण

	ubiblock_devs++;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops ubiblock_param_ops = अणु
	.set    = ubiblock_set_param,
पूर्ण;
module_param_cb(block, &ubiblock_param_ops, शून्य, 0);
MODULE_PARM_DESC(block, "Attach block devices to UBI volumes. Parameter format: block=<path|dev,num|dev,name>.\n"
			"Multiple \"block\" parameters may be specified.\n"
			"UBI volumes may be specified by their number, name, or path to the device node.\n"
			"Examples\n"
			"Using the UBI volume path:\n"
			"ubi.block=/dev/ubi0_0\n"
			"Using the UBI device, and the volume name:\n"
			"ubi.block=0,rootfs\n"
			"Using both UBI device number and UBI volume number:\n"
			"ubi.block=0,0\n");

अटल काष्ठा ubiblock *find_dev_nolock(पूर्णांक ubi_num, पूर्णांक vol_id)
अणु
	काष्ठा ubiblock *dev;

	list_क्रम_each_entry(dev, &ubiblock_devices, list)
		अगर (dev->ubi_num == ubi_num && dev->vol_id == vol_id)
			वापस dev;
	वापस शून्य;
पूर्ण

अटल पूर्णांक ubiblock_पढ़ो(काष्ठा ubiblock_pdu *pdu)
अणु
	पूर्णांक ret, leb, offset, bytes_left, to_पढ़ो;
	u64 pos;
	काष्ठा request *req = blk_mq_rq_from_pdu(pdu);
	काष्ठा ubiblock *dev = req->q->queuedata;

	to_पढ़ो = blk_rq_bytes(req);
	pos = blk_rq_pos(req) << 9;

	/* Get LEB:offset address to पढ़ो from */
	offset = करो_भाग(pos, dev->leb_size);
	leb = pos;
	bytes_left = to_पढ़ो;

	जबतक (bytes_left) अणु
		/*
		 * We can only पढ़ो one LEB at a समय. Thereक्रमe अगर the पढ़ो
		 * length is larger than one LEB size, we split the operation.
		 */
		अगर (offset + to_पढ़ो > dev->leb_size)
			to_पढ़ो = dev->leb_size - offset;

		ret = ubi_पढ़ो_sg(dev->desc, leb, &pdu->usgl, offset, to_पढ़ो);
		अगर (ret < 0)
			वापस ret;

		bytes_left -= to_पढ़ो;
		to_पढ़ो = bytes_left;
		leb += 1;
		offset = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ubiblock_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा ubiblock *dev = bdev->bd_disk->निजी_data;
	पूर्णांक ret;

	mutex_lock(&dev->dev_mutex);
	अगर (dev->refcnt > 0) अणु
		/*
		 * The volume is alपढ़ोy खोलो, just increase the reference
		 * counter.
		 */
		जाओ out_करोne;
	पूर्ण

	/*
	 * We want users to be aware they should only mount us as पढ़ो-only.
	 * It's just a paranoid check, as ग_लिखो requests will get rejected
	 * in any हाल.
	 */
	अगर (mode & FMODE_WRITE) अणु
		ret = -EROFS;
		जाओ out_unlock;
	पूर्ण

	dev->desc = ubi_खोलो_volume(dev->ubi_num, dev->vol_id, UBI_READONLY);
	अगर (IS_ERR(dev->desc)) अणु
		dev_err(disk_to_dev(dev->gd), "failed to open ubi volume %d_%d",
			dev->ubi_num, dev->vol_id);
		ret = PTR_ERR(dev->desc);
		dev->desc = शून्य;
		जाओ out_unlock;
	पूर्ण

out_करोne:
	dev->refcnt++;
	mutex_unlock(&dev->dev_mutex);
	वापस 0;

out_unlock:
	mutex_unlock(&dev->dev_mutex);
	वापस ret;
पूर्ण

अटल व्योम ubiblock_release(काष्ठा gendisk *gd, भ_शेषe_t mode)
अणु
	काष्ठा ubiblock *dev = gd->निजी_data;

	mutex_lock(&dev->dev_mutex);
	dev->refcnt--;
	अगर (dev->refcnt == 0) अणु
		ubi_बंद_volume(dev->desc);
		dev->desc = शून्य;
	पूर्ण
	mutex_unlock(&dev->dev_mutex);
पूर्ण

अटल पूर्णांक ubiblock_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo)
अणु
	/* Some tools might require this inक्रमmation */
	geo->heads = 1;
	geo->cylinders = 1;
	geo->sectors = get_capacity(bdev->bd_disk);
	geo->start = 0;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा block_device_operations ubiblock_ops = अणु
	.owner = THIS_MODULE,
	.खोलो = ubiblock_खोलो,
	.release = ubiblock_release,
	.getgeo	= ubiblock_getgeo,
पूर्ण;

अटल व्योम ubiblock_करो_work(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक ret;
	काष्ठा ubiblock_pdu *pdu = container_of(work, काष्ठा ubiblock_pdu, work);
	काष्ठा request *req = blk_mq_rq_from_pdu(pdu);

	blk_mq_start_request(req);

	/*
	 * It is safe to ignore the वापस value of blk_rq_map_sg() because
	 * the number of sg entries is limited to UBI_MAX_SG_COUNT
	 * and ubi_पढ़ो_sg() will check that limit.
	 */
	blk_rq_map_sg(req->q, req, pdu->usgl.sg);

	ret = ubiblock_पढ़ो(pdu);
	rq_flush_dcache_pages(req);

	blk_mq_end_request(req, त्रुटि_सं_to_blk_status(ret));
पूर्ण

अटल blk_status_t ubiblock_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
			     स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा request *req = bd->rq;
	काष्ठा ubiblock *dev = hctx->queue->queuedata;
	काष्ठा ubiblock_pdu *pdu = blk_mq_rq_to_pdu(req);

	चयन (req_op(req)) अणु
	हाल REQ_OP_READ:
		ubi_sgl_init(&pdu->usgl);
		queue_work(dev->wq, &pdu->work);
		वापस BLK_STS_OK;
	शेष:
		वापस BLK_STS_IOERR;
	पूर्ण

पूर्ण

अटल पूर्णांक ubiblock_init_request(काष्ठा blk_mq_tag_set *set,
		काष्ठा request *req, अचिन्हित पूर्णांक hctx_idx,
		अचिन्हित पूर्णांक numa_node)
अणु
	काष्ठा ubiblock_pdu *pdu = blk_mq_rq_to_pdu(req);

	sg_init_table(pdu->usgl.sg, UBI_MAX_SG_COUNT);
	INIT_WORK(&pdu->work, ubiblock_करो_work);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा blk_mq_ops ubiblock_mq_ops = अणु
	.queue_rq       = ubiblock_queue_rq,
	.init_request	= ubiblock_init_request,
पूर्ण;

अटल पूर्णांक calc_disk_capacity(काष्ठा ubi_volume_info *vi, u64 *disk_capacity)
अणु
	u64 size = vi->used_bytes >> 9;

	अगर (vi->used_bytes % 512) अणु
		pr_warn("UBI: block: volume size is not a multiple of 512, "
			"last %llu bytes are ignored!\n",
			vi->used_bytes - (size << 9));
	पूर्ण

	अगर ((sector_t)size != size)
		वापस -EFBIG;

	*disk_capacity = size;

	वापस 0;
पूर्ण

पूर्णांक ubiblock_create(काष्ठा ubi_volume_info *vi)
अणु
	काष्ठा ubiblock *dev;
	काष्ठा gendisk *gd;
	u64 disk_capacity;
	पूर्णांक ret;

	ret = calc_disk_capacity(vi, &disk_capacity);
	अगर (ret) अणु
		वापस ret;
	पूर्ण

	/* Check that the volume isn't alपढ़ोy handled */
	mutex_lock(&devices_mutex);
	अगर (find_dev_nolock(vi->ubi_num, vi->vol_id)) अणु
		ret = -EEXIST;
		जाओ out_unlock;
	पूर्ण

	dev = kzalloc(माप(काष्ठा ubiblock), GFP_KERNEL);
	अगर (!dev) अणु
		ret = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	mutex_init(&dev->dev_mutex);

	dev->ubi_num = vi->ubi_num;
	dev->vol_id = vi->vol_id;
	dev->leb_size = vi->usable_leb_size;

	/* Initialize the gendisk of this ubiblock device */
	gd = alloc_disk(1);
	अगर (!gd) अणु
		pr_err("UBI: block: alloc_disk failed\n");
		ret = -ENODEV;
		जाओ out_मुक्त_dev;
	पूर्ण

	gd->fops = &ubiblock_ops;
	gd->major = ubiblock_major;
	gd->first_minor = idr_alloc(&ubiblock_minor_idr, dev, 0, 0, GFP_KERNEL);
	अगर (gd->first_minor < 0) अणु
		dev_err(disk_to_dev(gd),
			"block: dynamic minor allocation failed");
		ret = -ENODEV;
		जाओ out_put_disk;
	पूर्ण
	gd->निजी_data = dev;
	प्र_लिखो(gd->disk_name, "ubiblock%d_%d", dev->ubi_num, dev->vol_id);
	set_capacity(gd, disk_capacity);
	dev->gd = gd;

	dev->tag_set.ops = &ubiblock_mq_ops;
	dev->tag_set.queue_depth = 64;
	dev->tag_set.numa_node = NUMA_NO_NODE;
	dev->tag_set.flags = BLK_MQ_F_SHOULD_MERGE;
	dev->tag_set.cmd_size = माप(काष्ठा ubiblock_pdu);
	dev->tag_set.driver_data = dev;
	dev->tag_set.nr_hw_queues = 1;

	ret = blk_mq_alloc_tag_set(&dev->tag_set);
	अगर (ret) अणु
		dev_err(disk_to_dev(dev->gd), "blk_mq_alloc_tag_set failed");
		जाओ out_हटाओ_minor;
	पूर्ण

	dev->rq = blk_mq_init_queue(&dev->tag_set);
	अगर (IS_ERR(dev->rq)) अणु
		dev_err(disk_to_dev(gd), "blk_mq_init_queue failed");
		ret = PTR_ERR(dev->rq);
		जाओ out_मुक्त_tags;
	पूर्ण
	blk_queue_max_segments(dev->rq, UBI_MAX_SG_COUNT);

	dev->rq->queuedata = dev;
	dev->gd->queue = dev->rq;

	/*
	 * Create one workqueue per volume (per रेजिस्टरed block device).
	 * Rembember workqueues are cheap, they're not thपढ़ोs.
	 */
	dev->wq = alloc_workqueue("%s", 0, 0, gd->disk_name);
	अगर (!dev->wq) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_queue;
	पूर्ण

	list_add_tail(&dev->list, &ubiblock_devices);

	/* Must be the last step: anyone can call file ops from now on */
	add_disk(dev->gd);
	dev_info(disk_to_dev(dev->gd), "created from ubi%d:%d(%s)",
		 dev->ubi_num, dev->vol_id, vi->name);
	mutex_unlock(&devices_mutex);
	वापस 0;

out_मुक्त_queue:
	blk_cleanup_queue(dev->rq);
out_मुक्त_tags:
	blk_mq_मुक्त_tag_set(&dev->tag_set);
out_हटाओ_minor:
	idr_हटाओ(&ubiblock_minor_idr, gd->first_minor);
out_put_disk:
	put_disk(dev->gd);
out_मुक्त_dev:
	kमुक्त(dev);
out_unlock:
	mutex_unlock(&devices_mutex);

	वापस ret;
पूर्ण

अटल व्योम ubiblock_cleanup(काष्ठा ubiblock *dev)
अणु
	/* Stop new requests to arrive */
	del_gendisk(dev->gd);
	/* Flush pending work */
	destroy_workqueue(dev->wq);
	/* Finally destroy the blk queue */
	blk_cleanup_queue(dev->rq);
	blk_mq_मुक्त_tag_set(&dev->tag_set);
	dev_info(disk_to_dev(dev->gd), "released");
	idr_हटाओ(&ubiblock_minor_idr, dev->gd->first_minor);
	put_disk(dev->gd);
पूर्ण

पूर्णांक ubiblock_हटाओ(काष्ठा ubi_volume_info *vi)
अणु
	काष्ठा ubiblock *dev;
	पूर्णांक ret;

	mutex_lock(&devices_mutex);
	dev = find_dev_nolock(vi->ubi_num, vi->vol_id);
	अगर (!dev) अणु
		ret = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	/* Found a device, let's lock it so we can check if it's busy */
	mutex_lock(&dev->dev_mutex);
	अगर (dev->refcnt > 0) अणु
		ret = -EBUSY;
		जाओ out_unlock_dev;
	पूर्ण

	/* Remove from device list */
	list_del(&dev->list);
	ubiblock_cleanup(dev);
	mutex_unlock(&dev->dev_mutex);
	mutex_unlock(&devices_mutex);

	kमुक्त(dev);
	वापस 0;

out_unlock_dev:
	mutex_unlock(&dev->dev_mutex);
out_unlock:
	mutex_unlock(&devices_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक ubiblock_resize(काष्ठा ubi_volume_info *vi)
अणु
	काष्ठा ubiblock *dev;
	u64 disk_capacity;
	पूर्णांक ret;

	/*
	 * Need to lock the device list until we stop using the device,
	 * otherwise the device काष्ठा might get released in
	 * 'ubiblock_remove()'.
	 */
	mutex_lock(&devices_mutex);
	dev = find_dev_nolock(vi->ubi_num, vi->vol_id);
	अगर (!dev) अणु
		mutex_unlock(&devices_mutex);
		वापस -ENODEV;
	पूर्ण

	ret = calc_disk_capacity(vi, &disk_capacity);
	अगर (ret) अणु
		mutex_unlock(&devices_mutex);
		अगर (ret == -EFBIG) अणु
			dev_warn(disk_to_dev(dev->gd),
				 "the volume is too big (%d LEBs), cannot resize",
				 vi->size);
		पूर्ण
		वापस ret;
	पूर्ण

	mutex_lock(&dev->dev_mutex);

	अगर (get_capacity(dev->gd) != disk_capacity) अणु
		set_capacity(dev->gd, disk_capacity);
		dev_info(disk_to_dev(dev->gd), "resized to %lld bytes",
			 vi->used_bytes);
	पूर्ण
	mutex_unlock(&dev->dev_mutex);
	mutex_unlock(&devices_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक ubiblock_notअगरy(काष्ठा notअगरier_block *nb,
			 अचिन्हित दीर्घ notअगरication_type, व्योम *ns_ptr)
अणु
	काष्ठा ubi_notअगरication *nt = ns_ptr;

	चयन (notअगरication_type) अणु
	हाल UBI_VOLUME_ADDED:
		/*
		 * We want to enक्रमce explicit block device creation क्रम
		 * volumes, so when a volume is added we करो nothing.
		 */
		अवरोध;
	हाल UBI_VOLUME_REMOVED:
		ubiblock_हटाओ(&nt->vi);
		अवरोध;
	हाल UBI_VOLUME_RESIZED:
		ubiblock_resize(&nt->vi);
		अवरोध;
	हाल UBI_VOLUME_UPDATED:
		/*
		 * If the volume is अटल, a content update might mean the
		 * size (i.e. used_bytes) was also changed.
		 */
		अगर (nt->vi.vol_type == UBI_STATIC_VOLUME)
			ubiblock_resize(&nt->vi);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block ubiblock_notअगरier = अणु
	.notअगरier_call = ubiblock_notअगरy,
पूर्ण;

अटल काष्ठा ubi_volume_desc * __init
खोलो_volume_desc(स्थिर अक्षर *name, पूर्णांक ubi_num, पूर्णांक vol_id)
अणु
	अगर (ubi_num == -1)
		/* No ubi num, name must be a vol device path */
		वापस ubi_खोलो_volume_path(name, UBI_READONLY);
	अन्यथा अगर (vol_id == -1)
		/* No vol_id, must be vol_name */
		वापस ubi_खोलो_volume_nm(ubi_num, name, UBI_READONLY);
	अन्यथा
		वापस ubi_खोलो_volume(ubi_num, vol_id, UBI_READONLY);
पूर्ण

अटल व्योम __init ubiblock_create_from_param(व्योम)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा ubiblock_param *p;
	काष्ठा ubi_volume_desc *desc;
	काष्ठा ubi_volume_info vi;

	/*
	 * If there is an error creating one of the ubiblocks, जारी on to
	 * create the following ubiblocks. This helps in a circumstance where
	 * the kernel command-line specअगरies multiple block devices and some
	 * may be broken, but we still want the working ones to come up.
	 */
	क्रम (i = 0; i < ubiblock_devs; i++) अणु
		p = &ubiblock_param[i];

		desc = खोलो_volume_desc(p->name, p->ubi_num, p->vol_id);
		अगर (IS_ERR(desc)) अणु
			pr_err(
			       "UBI: block: can't open volume on ubi%d_%d, err=%ld\n",
			       p->ubi_num, p->vol_id, PTR_ERR(desc));
			जारी;
		पूर्ण

		ubi_get_volume_info(desc, &vi);
		ubi_बंद_volume(desc);

		ret = ubiblock_create(&vi);
		अगर (ret) अणु
			pr_err(
			       "UBI: block: can't add '%s' volume on ubi%d_%d, err=%d\n",
			       vi.name, p->ubi_num, p->vol_id, ret);
			जारी;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ubiblock_हटाओ_all(व्योम)
अणु
	काष्ठा ubiblock *next;
	काष्ठा ubiblock *dev;

	mutex_lock(&devices_mutex);
	list_क्रम_each_entry_safe(dev, next, &ubiblock_devices, list) अणु
		/* The module is being क्रमcefully हटाओd */
		WARN_ON(dev->desc);
		/* Remove from device list */
		list_del(&dev->list);
		ubiblock_cleanup(dev);
		kमुक्त(dev);
	पूर्ण
	mutex_unlock(&devices_mutex);
पूर्ण

पूर्णांक __init ubiblock_init(व्योम)
अणु
	पूर्णांक ret;

	ubiblock_major = रेजिस्टर_blkdev(0, "ubiblock");
	अगर (ubiblock_major < 0)
		वापस ubiblock_major;

	/*
	 * Attach block devices from 'block=' module param.
	 * Even अगर one block device in the param list fails to come up,
	 * still allow the module to load and leave any others up.
	 */
	ubiblock_create_from_param();

	/*
	 * Block devices are only created upon user requests, so we ignore
	 * existing volumes.
	 */
	ret = ubi_रेजिस्टर_volume_notअगरier(&ubiblock_notअगरier, 1);
	अगर (ret)
		जाओ err_unreg;
	वापस 0;

err_unreg:
	unरेजिस्टर_blkdev(ubiblock_major, "ubiblock");
	ubiblock_हटाओ_all();
	वापस ret;
पूर्ण

व्योम __निकास ubiblock_निकास(व्योम)
अणु
	ubi_unरेजिस्टर_volume_notअगरier(&ubiblock_notअगरier);
	ubiblock_हटाओ_all();
	unरेजिस्टर_blkdev(ubiblock_major, "ubiblock");
पूर्ण
