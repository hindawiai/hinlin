<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Interface to Linux block layer क्रम MTD 'translation layers'.
 *
 * Copyright तऊ 2003-2010 David Woodhouse <dwmw2@infradead.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/fs.h>
#समावेश <linux/mtd/blktrans.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/blkpg.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>

#समावेश "mtdcore.h"

अटल LIST_HEAD(blktrans_majors);
अटल DEFINE_MUTEX(blktrans_ref_mutex);

अटल व्योम blktrans_dev_release(काष्ठा kref *kref)
अणु
	काष्ठा mtd_blktrans_dev *dev =
		container_of(kref, काष्ठा mtd_blktrans_dev, ref);

	dev->disk->निजी_data = शून्य;
	blk_cleanup_queue(dev->rq);
	blk_mq_मुक्त_tag_set(dev->tag_set);
	kमुक्त(dev->tag_set);
	put_disk(dev->disk);
	list_del(&dev->list);
	kमुक्त(dev);
पूर्ण

अटल काष्ठा mtd_blktrans_dev *blktrans_dev_get(काष्ठा gendisk *disk)
अणु
	काष्ठा mtd_blktrans_dev *dev;

	mutex_lock(&blktrans_ref_mutex);
	dev = disk->निजी_data;

	अगर (!dev)
		जाओ unlock;
	kref_get(&dev->ref);
unlock:
	mutex_unlock(&blktrans_ref_mutex);
	वापस dev;
पूर्ण

अटल व्योम blktrans_dev_put(काष्ठा mtd_blktrans_dev *dev)
अणु
	mutex_lock(&blktrans_ref_mutex);
	kref_put(&dev->ref, blktrans_dev_release);
	mutex_unlock(&blktrans_ref_mutex);
पूर्ण


अटल blk_status_t करो_blktrans_request(काष्ठा mtd_blktrans_ops *tr,
			       काष्ठा mtd_blktrans_dev *dev,
			       काष्ठा request *req)
अणु
	अचिन्हित दीर्घ block, nsect;
	अक्षर *buf;

	block = blk_rq_pos(req) << 9 >> tr->blkshअगरt;
	nsect = blk_rq_cur_bytes(req) >> tr->blkshअगरt;

	अगर (req_op(req) == REQ_OP_FLUSH) अणु
		अगर (tr->flush(dev))
			वापस BLK_STS_IOERR;
		वापस BLK_STS_OK;
	पूर्ण

	अगर (blk_rq_pos(req) + blk_rq_cur_sectors(req) >
	    get_capacity(req->rq_disk))
		वापस BLK_STS_IOERR;

	चयन (req_op(req)) अणु
	हाल REQ_OP_DISCARD:
		अगर (tr->discard(dev, block, nsect))
			वापस BLK_STS_IOERR;
		वापस BLK_STS_OK;
	हाल REQ_OP_READ:
		buf = kmap(bio_page(req->bio)) + bio_offset(req->bio);
		क्रम (; nsect > 0; nsect--, block++, buf += tr->blksize) अणु
			अगर (tr->पढ़ोsect(dev, block, buf)) अणु
				kunmap(bio_page(req->bio));
				वापस BLK_STS_IOERR;
			पूर्ण
		पूर्ण
		kunmap(bio_page(req->bio));
		rq_flush_dcache_pages(req);
		वापस BLK_STS_OK;
	हाल REQ_OP_WRITE:
		अगर (!tr->ग_लिखोsect)
			वापस BLK_STS_IOERR;

		rq_flush_dcache_pages(req);
		buf = kmap(bio_page(req->bio)) + bio_offset(req->bio);
		क्रम (; nsect > 0; nsect--, block++, buf += tr->blksize) अणु
			अगर (tr->ग_लिखोsect(dev, block, buf)) अणु
				kunmap(bio_page(req->bio));
				वापस BLK_STS_IOERR;
			पूर्ण
		पूर्ण
		kunmap(bio_page(req->bio));
		वापस BLK_STS_OK;
	शेष:
		वापस BLK_STS_IOERR;
	पूर्ण
पूर्ण

पूर्णांक mtd_blktrans_cease_background(काष्ठा mtd_blktrans_dev *dev)
अणु
	वापस dev->bg_stop;
पूर्ण
EXPORT_SYMBOL_GPL(mtd_blktrans_cease_background);

अटल काष्ठा request *mtd_next_request(काष्ठा mtd_blktrans_dev *dev)
अणु
	काष्ठा request *rq;

	rq = list_first_entry_or_null(&dev->rq_list, काष्ठा request, queuelist);
	अगर (rq) अणु
		list_del_init(&rq->queuelist);
		blk_mq_start_request(rq);
		वापस rq;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम mtd_blktrans_work(काष्ठा mtd_blktrans_dev *dev)
	__releases(&dev->queue_lock)
	__acquires(&dev->queue_lock)
अणु
	काष्ठा mtd_blktrans_ops *tr = dev->tr;
	काष्ठा request *req = शून्य;
	पूर्णांक background_करोne = 0;

	जबतक (1) अणु
		blk_status_t res;

		dev->bg_stop = false;
		अगर (!req && !(req = mtd_next_request(dev))) अणु
			अगर (tr->background && !background_करोne) अणु
				spin_unlock_irq(&dev->queue_lock);
				mutex_lock(&dev->lock);
				tr->background(dev);
				mutex_unlock(&dev->lock);
				spin_lock_irq(&dev->queue_lock);
				/*
				 * Do background processing just once per idle
				 * period.
				 */
				background_करोne = !dev->bg_stop;
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण

		spin_unlock_irq(&dev->queue_lock);

		mutex_lock(&dev->lock);
		res = करो_blktrans_request(dev->tr, dev, req);
		mutex_unlock(&dev->lock);

		अगर (!blk_update_request(req, res, blk_rq_cur_bytes(req))) अणु
			__blk_mq_end_request(req, res);
			req = शून्य;
		पूर्ण

		background_करोne = 0;
		spin_lock_irq(&dev->queue_lock);
	पूर्ण
पूर्ण

अटल blk_status_t mtd_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				 स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा mtd_blktrans_dev *dev;

	dev = hctx->queue->queuedata;
	अगर (!dev) अणु
		blk_mq_start_request(bd->rq);
		वापस BLK_STS_IOERR;
	पूर्ण

	spin_lock_irq(&dev->queue_lock);
	list_add_tail(&bd->rq->queuelist, &dev->rq_list);
	mtd_blktrans_work(dev);
	spin_unlock_irq(&dev->queue_lock);

	वापस BLK_STS_OK;
पूर्ण

अटल पूर्णांक blktrans_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा mtd_blktrans_dev *dev = blktrans_dev_get(bdev->bd_disk);
	पूर्णांक ret = 0;

	अगर (!dev)
		वापस -ERESTARTSYS; /* FIXME: busy loop! -arnd*/

	mutex_lock(&mtd_table_mutex);
	mutex_lock(&dev->lock);

	अगर (dev->खोलो)
		जाओ unlock;

	kref_get(&dev->ref);
	__module_get(dev->tr->owner);

	अगर (!dev->mtd)
		जाओ unlock;

	अगर (dev->tr->खोलो) अणु
		ret = dev->tr->खोलो(dev);
		अगर (ret)
			जाओ error_put;
	पूर्ण

	ret = __get_mtd_device(dev->mtd);
	अगर (ret)
		जाओ error_release;
	dev->file_mode = mode;

unlock:
	dev->खोलो++;
	mutex_unlock(&dev->lock);
	mutex_unlock(&mtd_table_mutex);
	blktrans_dev_put(dev);
	वापस ret;

error_release:
	अगर (dev->tr->release)
		dev->tr->release(dev);
error_put:
	module_put(dev->tr->owner);
	kref_put(&dev->ref, blktrans_dev_release);
	mutex_unlock(&dev->lock);
	mutex_unlock(&mtd_table_mutex);
	blktrans_dev_put(dev);
	वापस ret;
पूर्ण

अटल व्योम blktrans_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा mtd_blktrans_dev *dev = blktrans_dev_get(disk);

	अगर (!dev)
		वापस;

	mutex_lock(&mtd_table_mutex);
	mutex_lock(&dev->lock);

	अगर (--dev->खोलो)
		जाओ unlock;

	kref_put(&dev->ref, blktrans_dev_release);
	module_put(dev->tr->owner);

	अगर (dev->mtd) अणु
		अगर (dev->tr->release)
			dev->tr->release(dev);
		__put_mtd_device(dev->mtd);
	पूर्ण
unlock:
	mutex_unlock(&dev->lock);
	mutex_unlock(&mtd_table_mutex);
	blktrans_dev_put(dev);
पूर्ण

अटल पूर्णांक blktrans_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo)
अणु
	काष्ठा mtd_blktrans_dev *dev = blktrans_dev_get(bdev->bd_disk);
	पूर्णांक ret = -ENXIO;

	अगर (!dev)
		वापस ret;

	mutex_lock(&dev->lock);

	अगर (!dev->mtd)
		जाओ unlock;

	ret = dev->tr->getgeo ? dev->tr->getgeo(dev, geo) : -ENOTTY;
unlock:
	mutex_unlock(&dev->lock);
	blktrans_dev_put(dev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा block_device_operations mtd_block_ops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= blktrans_खोलो,
	.release	= blktrans_release,
	.getgeo		= blktrans_getgeo,
पूर्ण;

अटल स्थिर काष्ठा blk_mq_ops mtd_mq_ops = अणु
	.queue_rq	= mtd_queue_rq,
पूर्ण;

पूर्णांक add_mtd_blktrans_dev(काष्ठा mtd_blktrans_dev *new)
अणु
	काष्ठा mtd_blktrans_ops *tr = new->tr;
	काष्ठा mtd_blktrans_dev *d;
	पूर्णांक last_devnum = -1;
	काष्ठा gendisk *gd;
	पूर्णांक ret;

	अगर (mutex_trylock(&mtd_table_mutex)) अणु
		mutex_unlock(&mtd_table_mutex);
		BUG();
	पूर्ण

	mutex_lock(&blktrans_ref_mutex);
	list_क्रम_each_entry(d, &tr->devs, list) अणु
		अगर (new->devnum == -1) अणु
			/* Use first मुक्त number */
			अगर (d->devnum != last_devnum+1) अणु
				/* Found a मुक्त devnum. Plug it in here */
				new->devnum = last_devnum+1;
				list_add_tail(&new->list, &d->list);
				जाओ added;
			पूर्ण
		पूर्ण अन्यथा अगर (d->devnum == new->devnum) अणु
			/* Required number taken */
			mutex_unlock(&blktrans_ref_mutex);
			वापस -EBUSY;
		पूर्ण अन्यथा अगर (d->devnum > new->devnum) अणु
			/* Required number was मुक्त */
			list_add_tail(&new->list, &d->list);
			जाओ added;
		पूर्ण
		last_devnum = d->devnum;
	पूर्ण

	ret = -EBUSY;
	अगर (new->devnum == -1)
		new->devnum = last_devnum+1;

	/* Check that the device and any partitions will get valid
	 * minor numbers and that the disk naming code below can cope
	 * with this number. */
	अगर (new->devnum > (MINORMASK >> tr->part_bits) ||
	    (tr->part_bits && new->devnum >= 27 * 26)) अणु
		mutex_unlock(&blktrans_ref_mutex);
		जाओ error1;
	पूर्ण

	list_add_tail(&new->list, &tr->devs);
 added:
	mutex_unlock(&blktrans_ref_mutex);

	mutex_init(&new->lock);
	kref_init(&new->ref);
	अगर (!tr->ग_लिखोsect)
		new->पढ़ोonly = 1;

	/* Create gendisk */
	ret = -ENOMEM;
	gd = alloc_disk(1 << tr->part_bits);

	अगर (!gd)
		जाओ error2;

	new->disk = gd;
	gd->निजी_data = new;
	gd->major = tr->major;
	gd->first_minor = (new->devnum) << tr->part_bits;
	gd->fops = &mtd_block_ops;

	अगर (tr->part_bits)
		अगर (new->devnum < 26)
			snम_लिखो(gd->disk_name, माप(gd->disk_name),
				 "%s%c", tr->name, 'a' + new->devnum);
		अन्यथा
			snम_लिखो(gd->disk_name, माप(gd->disk_name),
				 "%s%c%c", tr->name,
				 'a' - 1 + new->devnum / 26,
				 'a' + new->devnum % 26);
	अन्यथा
		snम_लिखो(gd->disk_name, माप(gd->disk_name),
			 "%s%d", tr->name, new->devnum);

	set_capacity(gd, ((u64)new->size * tr->blksize) >> 9);

	/* Create the request queue */
	spin_lock_init(&new->queue_lock);
	INIT_LIST_HEAD(&new->rq_list);

	new->tag_set = kzalloc(माप(*new->tag_set), GFP_KERNEL);
	अगर (!new->tag_set)
		जाओ error3;

	new->rq = blk_mq_init_sq_queue(new->tag_set, &mtd_mq_ops, 2,
				BLK_MQ_F_SHOULD_MERGE | BLK_MQ_F_BLOCKING);
	अगर (IS_ERR(new->rq)) अणु
		ret = PTR_ERR(new->rq);
		new->rq = शून्य;
		जाओ error4;
	पूर्ण

	अगर (tr->flush)
		blk_queue_ग_लिखो_cache(new->rq, true, false);

	new->rq->queuedata = new;
	blk_queue_logical_block_size(new->rq, tr->blksize);

	blk_queue_flag_set(QUEUE_FLAG_NONROT, new->rq);
	blk_queue_flag_clear(QUEUE_FLAG_ADD_RANDOM, new->rq);

	अगर (tr->discard) अणु
		blk_queue_flag_set(QUEUE_FLAG_DISCARD, new->rq);
		blk_queue_max_discard_sectors(new->rq, अच_पूर्णांक_उच्च);
	पूर्ण

	gd->queue = new->rq;

	अगर (new->पढ़ोonly)
		set_disk_ro(gd, 1);

	device_add_disk(&new->mtd->dev, gd, शून्य);

	अगर (new->disk_attributes) अणु
		ret = sysfs_create_group(&disk_to_dev(gd)->kobj,
					new->disk_attributes);
		WARN_ON(ret);
	पूर्ण
	वापस 0;
error4:
	kमुक्त(new->tag_set);
error3:
	put_disk(new->disk);
error2:
	list_del(&new->list);
error1:
	वापस ret;
पूर्ण

पूर्णांक del_mtd_blktrans_dev(काष्ठा mtd_blktrans_dev *old)
अणु
	अचिन्हित दीर्घ flags;

	अगर (mutex_trylock(&mtd_table_mutex)) अणु
		mutex_unlock(&mtd_table_mutex);
		BUG();
	पूर्ण

	अगर (old->disk_attributes)
		sysfs_हटाओ_group(&disk_to_dev(old->disk)->kobj,
						old->disk_attributes);

	/* Stop new requests to arrive */
	del_gendisk(old->disk);

	/* Kill current requests */
	spin_lock_irqsave(&old->queue_lock, flags);
	old->rq->queuedata = शून्य;
	spin_unlock_irqrestore(&old->queue_lock, flags);

	/* मुक्तze+quiesce queue to ensure all requests are flushed */
	blk_mq_मुक्तze_queue(old->rq);
	blk_mq_quiesce_queue(old->rq);
	blk_mq_unquiesce_queue(old->rq);
	blk_mq_unमुक्तze_queue(old->rq);

	/* If the device is currently खोलो, tell trans driver to बंद it,
		then put mtd device, and करोn't touch it again */
	mutex_lock(&old->lock);
	अगर (old->खोलो) अणु
		अगर (old->tr->release)
			old->tr->release(old);
		__put_mtd_device(old->mtd);
	पूर्ण

	old->mtd = शून्य;

	mutex_unlock(&old->lock);
	blktrans_dev_put(old);
	वापस 0;
पूर्ण

अटल व्योम blktrans_notअगरy_हटाओ(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_blktrans_ops *tr;
	काष्ठा mtd_blktrans_dev *dev, *next;

	list_क्रम_each_entry(tr, &blktrans_majors, list)
		list_क्रम_each_entry_safe(dev, next, &tr->devs, list)
			अगर (dev->mtd == mtd)
				tr->हटाओ_dev(dev);
पूर्ण

अटल व्योम blktrans_notअगरy_add(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_blktrans_ops *tr;

	अगर (mtd->type == MTD_ABSENT)
		वापस;

	list_क्रम_each_entry(tr, &blktrans_majors, list)
		tr->add_mtd(tr, mtd);
पूर्ण

अटल काष्ठा mtd_notअगरier blktrans_notअगरier = अणु
	.add = blktrans_notअगरy_add,
	.हटाओ = blktrans_notअगरy_हटाओ,
पूर्ण;

पूर्णांक रेजिस्टर_mtd_blktrans(काष्ठा mtd_blktrans_ops *tr)
अणु
	काष्ठा mtd_info *mtd;
	पूर्णांक ret;

	/* Register the notअगरier अगर/when the first device type is
	   रेजिस्टरed, to prevent the link/init ordering from fucking
	   us over. */
	अगर (!blktrans_notअगरier.list.next)
		रेजिस्टर_mtd_user(&blktrans_notअगरier);


	mutex_lock(&mtd_table_mutex);

	ret = रेजिस्टर_blkdev(tr->major, tr->name);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_WARNING "Unable to register %s block device on major %d: %d\n",
		       tr->name, tr->major, ret);
		mutex_unlock(&mtd_table_mutex);
		वापस ret;
	पूर्ण

	अगर (ret)
		tr->major = ret;

	tr->blkshअगरt = ffs(tr->blksize) - 1;

	INIT_LIST_HEAD(&tr->devs);
	list_add(&tr->list, &blktrans_majors);

	mtd_क्रम_each_device(mtd)
		अगर (mtd->type != MTD_ABSENT)
			tr->add_mtd(tr, mtd);

	mutex_unlock(&mtd_table_mutex);
	वापस 0;
पूर्ण

पूर्णांक deरेजिस्टर_mtd_blktrans(काष्ठा mtd_blktrans_ops *tr)
अणु
	काष्ठा mtd_blktrans_dev *dev, *next;

	mutex_lock(&mtd_table_mutex);

	/* Remove it from the list of active majors */
	list_del(&tr->list);

	list_क्रम_each_entry_safe(dev, next, &tr->devs, list)
		tr->हटाओ_dev(dev);

	unरेजिस्टर_blkdev(tr->major, tr->name);
	mutex_unlock(&mtd_table_mutex);

	BUG_ON(!list_empty(&tr->devs));
	वापस 0;
पूर्ण

अटल व्योम __निकास mtd_blktrans_निकास(व्योम)
अणु
	/* No race here -- अगर someone's currently in रेजिस्टर_mtd_blktrans
	   we're screwed anyway. */
	अगर (blktrans_notअगरier.list.next)
		unरेजिस्टर_mtd_user(&blktrans_notअगरier);
पूर्ण

module_निकास(mtd_blktrans_निकास);

EXPORT_SYMBOL_GPL(रेजिस्टर_mtd_blktrans);
EXPORT_SYMBOL_GPL(deरेजिस्टर_mtd_blktrans);
EXPORT_SYMBOL_GPL(add_mtd_blktrans_dev);
EXPORT_SYMBOL_GPL(del_mtd_blktrans_dev);

MODULE_AUTHOR("David Woodhouse <dwmw2@infradead.org>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Common interface to block layer for MTD 'translation layers'");
