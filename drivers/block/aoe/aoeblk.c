<शैली गुरु>
/* Copyright (c) 2013 Coraid, Inc.  See COPYING क्रम GPL terms. */
/*
 * aoeblk.c
 * block device routines
 */

#समावेश <linux/kernel.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/fs.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/slab.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/genhd.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/mutex.h>
#समावेश <linux/export.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/debugfs.h>
#समावेश <scsi/sg.h>
#समावेश "aoe.h"

अटल DEFINE_MUTEX(aoeblk_mutex);
अटल काष्ठा kmem_cache *buf_pool_cache;
अटल काष्ठा dentry *aoe_debugfs_dir;

/* GPFS needs a larger value than the शेष. */
अटल पूर्णांक aoe_maxsectors;
module_param(aoe_maxsectors, पूर्णांक, 0644);
MODULE_PARM_DESC(aoe_maxsectors,
	"When nonzero, set the maximum number of sectors per I/O request");

अटल sमाप_प्रकार aoedisk_show_state(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *page)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);
	काष्ठा aoedev *d = disk->निजी_data;

	वापस snम_लिखो(page, PAGE_SIZE,
			"%s%s\n",
			(d->flags & DEVFL_UP) ? "up" : "down",
			(d->flags & DEVFL_KICKME) ? ",kickme" :
			(d->nखोलो && !(d->flags & DEVFL_UP)) ? ",closewait" : "");
	/* I'd rather see nखोलो exported so we can ditch बंदरुको */
पूर्ण
अटल sमाप_प्रकार aoedisk_show_mac(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *page)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);
	काष्ठा aoedev *d = disk->निजी_data;
	काष्ठा aoetgt *t = d->tarमाला_लो[0];

	अगर (t == शून्य)
		वापस snम_लिखो(page, PAGE_SIZE, "none\n");
	वापस snम_लिखो(page, PAGE_SIZE, "%pm\n", t->addr);
पूर्ण
अटल sमाप_प्रकार aoedisk_show_netअगर(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *page)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);
	काष्ठा aoedev *d = disk->निजी_data;
	काष्ठा net_device *nds[8], **nd, **nnd, **ne;
	काष्ठा aoetgt **t, **te;
	काष्ठा aoeअगर *अगरp, *e;
	अक्षर *p;

	स_रखो(nds, 0, माप nds);
	nd = nds;
	ne = nd + ARRAY_SIZE(nds);
	t = d->tarमाला_लो;
	te = t + d->ntarमाला_लो;
	क्रम (; t < te && *t; t++) अणु
		अगरp = (*t)->अगरs;
		e = अगरp + NAOEIFS;
		क्रम (; अगरp < e && अगरp->nd; अगरp++) अणु
			क्रम (nnd = nds; nnd < nd; nnd++)
				अगर (*nnd == अगरp->nd)
					अवरोध;
			अगर (nnd == nd && nd != ne)
				*nd++ = अगरp->nd;
		पूर्ण
	पूर्ण

	ne = nd;
	nd = nds;
	अगर (*nd == शून्य)
		वापस snम_लिखो(page, PAGE_SIZE, "none\n");
	क्रम (p = page; nd < ne; nd++)
		p += scnम_लिखो(p, PAGE_SIZE - (p-page), "%s%s",
			p == page ? "" : ",", (*nd)->name);
	p += scnम_लिखो(p, PAGE_SIZE - (p-page), "\n");
	वापस p-page;
पूर्ण
/* firmware version */
अटल sमाप_प्रकार aoedisk_show_fwver(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *page)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);
	काष्ठा aoedev *d = disk->निजी_data;

	वापस snम_लिखो(page, PAGE_SIZE, "0x%04x\n", (अचिन्हित पूर्णांक) d->fw_ver);
पूर्ण
अटल sमाप_प्रकार aoedisk_show_payload(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *page)
अणु
	काष्ठा gendisk *disk = dev_to_disk(dev);
	काष्ठा aoedev *d = disk->निजी_data;

	वापस snम_लिखो(page, PAGE_SIZE, "%lu\n", d->maxbcnt);
पूर्ण

अटल पूर्णांक aoedisk_debugfs_show(काष्ठा seq_file *s, व्योम *ignored)
अणु
	काष्ठा aoedev *d;
	काष्ठा aoetgt **t, **te;
	काष्ठा aoeअगर *अगरp, *अगरe;
	अचिन्हित दीर्घ flags;
	अक्षर c;

	d = s->निजी;
	seq_म_लिखो(s, "rttavg: %d rttdev: %d\n",
		d->rttavg >> RTTSCALE,
		d->rttdev >> RTTDSCALE);
	seq_म_लिखो(s, "nskbpool: %d\n", skb_queue_len(&d->skbpool));
	seq_म_लिखो(s, "kicked: %ld\n", d->kicked);
	seq_म_लिखो(s, "maxbcnt: %ld\n", d->maxbcnt);
	seq_म_लिखो(s, "ref: %ld\n", d->ref);

	spin_lock_irqsave(&d->lock, flags);
	t = d->tarमाला_लो;
	te = t + d->ntarमाला_लो;
	क्रम (; t < te && *t; t++) अणु
		c = '\t';
		seq_म_लिखो(s, "falloc: %ld\n", (*t)->falloc);
		seq_म_लिखो(s, "ffree: %p\n",
			list_empty(&(*t)->fमुक्त) ? शून्य : (*t)->fमुक्त.next);
		seq_म_लिखो(s, "%pm:%d:%d:%d\n", (*t)->addr, (*t)->nout,
			(*t)->maxout, (*t)->nframes);
		seq_म_लिखो(s, "\tssthresh:%d\n", (*t)->ssthresh);
		seq_म_लिखो(s, "\ttaint:%d\n", (*t)->taपूर्णांक);
		seq_म_लिखो(s, "\tr:%d\n", (*t)->rpkts);
		seq_म_लिखो(s, "\tw:%d\n", (*t)->wpkts);
		अगरp = (*t)->अगरs;
		अगरe = अगरp + ARRAY_SIZE((*t)->अगरs);
		क्रम (; अगरp->nd && अगरp < अगरe; अगरp++) अणु
			seq_म_लिखो(s, "%c%s", c, अगरp->nd->name);
			c = ',';
		पूर्ण
		seq_माला_दो(s, "\n");
	पूर्ण
	spin_unlock_irqrestore(&d->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक aoe_debugfs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, aoedisk_debugfs_show, inode->i_निजी);
पूर्ण

अटल DEVICE_ATTR(state, 0444, aoedisk_show_state, शून्य);
अटल DEVICE_ATTR(mac, 0444, aoedisk_show_mac, शून्य);
अटल DEVICE_ATTR(netअगर, 0444, aoedisk_show_netअगर, शून्य);
अटल काष्ठा device_attribute dev_attr_firmware_version = अणु
	.attr = अणु .name = "firmware-version", .mode = 0444 पूर्ण,
	.show = aoedisk_show_fwver,
पूर्ण;
अटल DEVICE_ATTR(payload, 0444, aoedisk_show_payload, शून्य);

अटल काष्ठा attribute *aoe_attrs[] = अणु
	&dev_attr_state.attr,
	&dev_attr_mac.attr,
	&dev_attr_netअगर.attr,
	&dev_attr_firmware_version.attr,
	&dev_attr_payload.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group aoe_attr_group = अणु
	.attrs = aoe_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *aoe_attr_groups[] = अणु
	&aoe_attr_group,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा file_operations aoe_debugfs_fops = अणु
	.खोलो = aoe_debugfs_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = single_release,
पूर्ण;

अटल व्योम
aoedisk_add_debugfs(काष्ठा aoedev *d)
अणु
	अक्षर *p;

	अगर (aoe_debugfs_dir == शून्य)
		वापस;
	p = म_अक्षर(d->gd->disk_name, '/');
	अगर (p == शून्य)
		p = d->gd->disk_name;
	अन्यथा
		p++;
	BUG_ON(*p == '\0');
	d->debugfs = debugfs_create_file(p, 0444, aoe_debugfs_dir, d,
					 &aoe_debugfs_fops);
पूर्ण
व्योम
aoedisk_rm_debugfs(काष्ठा aoedev *d)
अणु
	debugfs_हटाओ(d->debugfs);
	d->debugfs = शून्य;
पूर्ण

अटल पूर्णांक
aoeblk_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा aoedev *d = bdev->bd_disk->निजी_data;
	uदीर्घ flags;

	अगर (!virt_addr_valid(d)) अणु
		pr_crit("aoe: invalid device pointer in %s\n",
			__func__);
		WARN_ON(1);
		वापस -ENODEV;
	पूर्ण
	अगर (!(d->flags & DEVFL_UP) || d->flags & DEVFL_TKILL)
		वापस -ENODEV;

	mutex_lock(&aoeblk_mutex);
	spin_lock_irqsave(&d->lock, flags);
	अगर (d->flags & DEVFL_UP && !(d->flags & DEVFL_TKILL)) अणु
		d->nखोलो++;
		spin_unlock_irqrestore(&d->lock, flags);
		mutex_unlock(&aoeblk_mutex);
		वापस 0;
	पूर्ण
	spin_unlock_irqrestore(&d->lock, flags);
	mutex_unlock(&aoeblk_mutex);
	वापस -ENODEV;
पूर्ण

अटल व्योम
aoeblk_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा aoedev *d = disk->निजी_data;
	uदीर्घ flags;

	spin_lock_irqsave(&d->lock, flags);

	अगर (--d->nखोलो == 0) अणु
		spin_unlock_irqrestore(&d->lock, flags);
		aoecmd_cfg(d->aoemajor, d->aoeminor);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&d->lock, flags);
पूर्ण

अटल blk_status_t aoeblk_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				    स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा aoedev *d = hctx->queue->queuedata;

	spin_lock_irq(&d->lock);

	अगर ((d->flags & DEVFL_UP) == 0) अणु
		pr_info_ratelimited("aoe: device %ld.%d is not up\n",
			d->aoemajor, d->aoeminor);
		spin_unlock_irq(&d->lock);
		blk_mq_start_request(bd->rq);
		वापस BLK_STS_IOERR;
	पूर्ण

	list_add_tail(&bd->rq->queuelist, &d->rq_list);
	aoecmd_work(d);
	spin_unlock_irq(&d->lock);
	वापस BLK_STS_OK;
पूर्ण

अटल पूर्णांक
aoeblk_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo)
अणु
	काष्ठा aoedev *d = bdev->bd_disk->निजी_data;

	अगर ((d->flags & DEVFL_UP) == 0) अणु
		prपूर्णांकk(KERN_ERR "aoe: disk not up\n");
		वापस -ENODEV;
	पूर्ण

	geo->cylinders = d->geo.cylinders;
	geo->heads = d->geo.heads;
	geo->sectors = d->geo.sectors;
	वापस 0;
पूर्ण

अटल पूर्णांक
aoeblk_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode, uपूर्णांक cmd, uदीर्घ arg)
अणु
	काष्ठा aoedev *d;

	अगर (!arg)
		वापस -EINVAL;

	d = bdev->bd_disk->निजी_data;
	अगर ((d->flags & DEVFL_UP) == 0) अणु
		pr_err("aoe: disk not up\n");
		वापस -ENODEV;
	पूर्ण

	अगर (cmd == HDIO_GET_IDENTITY) अणु
		अगर (!copy_to_user((व्योम __user *) arg, &d->ident,
			माप(d->ident)))
			वापस 0;
		वापस -EFAULT;
	पूर्ण

	/* udev calls scsi_id, which uses SG_IO, resulting in noise */
	अगर (cmd != SG_IO)
		pr_info("aoe: unknown ioctl 0x%x\n", cmd);

	वापस -ENOTTY;
पूर्ण

अटल स्थिर काष्ठा block_device_operations aoe_bकरोps = अणु
	.खोलो = aoeblk_खोलो,
	.release = aoeblk_release,
	.ioctl = aoeblk_ioctl,
	.compat_ioctl = blkdev_compat_ptr_ioctl,
	.getgeo = aoeblk_getgeo,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा blk_mq_ops aoeblk_mq_ops = अणु
	.queue_rq	= aoeblk_queue_rq,
पूर्ण;

/* alloc_disk and add_disk can sleep */
व्योम
aoeblk_gdalloc(व्योम *vp)
अणु
	काष्ठा aoedev *d = vp;
	काष्ठा gendisk *gd;
	mempool_t *mp;
	काष्ठा request_queue *q;
	काष्ठा blk_mq_tag_set *set;
	uदीर्घ flags;
	पूर्णांक late = 0;
	पूर्णांक err;

	spin_lock_irqsave(&d->lock, flags);
	अगर (d->flags & DEVFL_GDALLOC
	&& !(d->flags & DEVFL_TKILL)
	&& !(d->flags & DEVFL_GD_NOW))
		d->flags |= DEVFL_GD_NOW;
	अन्यथा
		late = 1;
	spin_unlock_irqrestore(&d->lock, flags);
	अगर (late)
		वापस;

	gd = alloc_disk(AOE_PARTITIONS);
	अगर (gd == शून्य) अणु
		pr_err("aoe: cannot allocate disk structure for %ld.%d\n",
			d->aoemajor, d->aoeminor);
		जाओ err;
	पूर्ण

	mp = mempool_create(MIN_BUFS, mempool_alloc_slab, mempool_मुक्त_slab,
		buf_pool_cache);
	अगर (mp == शून्य) अणु
		prपूर्णांकk(KERN_ERR "aoe: cannot allocate bufpool for %ld.%d\n",
			d->aoemajor, d->aoeminor);
		जाओ err_disk;
	पूर्ण

	set = &d->tag_set;
	set->ops = &aoeblk_mq_ops;
	set->cmd_size = माप(काष्ठा aoe_req);
	set->nr_hw_queues = 1;
	set->queue_depth = 128;
	set->numa_node = NUMA_NO_NODE;
	set->flags = BLK_MQ_F_SHOULD_MERGE;
	err = blk_mq_alloc_tag_set(set);
	अगर (err) अणु
		pr_err("aoe: cannot allocate tag set for %ld.%d\n",
			d->aoemajor, d->aoeminor);
		जाओ err_mempool;
	पूर्ण

	q = blk_mq_init_queue(set);
	अगर (IS_ERR(q)) अणु
		pr_err("aoe: cannot allocate block queue for %ld.%d\n",
			d->aoemajor, d->aoeminor);
		blk_mq_मुक्त_tag_set(set);
		जाओ err_mempool;
	पूर्ण

	spin_lock_irqsave(&d->lock, flags);
	WARN_ON(!(d->flags & DEVFL_GD_NOW));
	WARN_ON(!(d->flags & DEVFL_GDALLOC));
	WARN_ON(d->flags & DEVFL_TKILL);
	WARN_ON(d->gd);
	WARN_ON(d->flags & DEVFL_UP);
	blk_queue_max_hw_sectors(q, BLK_DEF_MAX_SECTORS);
	blk_queue_io_opt(q, SZ_2M);
	d->bufpool = mp;
	d->blkq = gd->queue = q;
	q->queuedata = d;
	d->gd = gd;
	अगर (aoe_maxsectors)
		blk_queue_max_hw_sectors(q, aoe_maxsectors);
	gd->major = AOE_MAJOR;
	gd->first_minor = d->sysminor;
	gd->fops = &aoe_bकरोps;
	gd->निजी_data = d;
	set_capacity(gd, d->ssize);
	snम_लिखो(gd->disk_name, माप gd->disk_name, "etherd/e%ld.%d",
		d->aoemajor, d->aoeminor);

	d->flags &= ~DEVFL_GDALLOC;
	d->flags |= DEVFL_UP;

	spin_unlock_irqrestore(&d->lock, flags);

	device_add_disk(शून्य, gd, aoe_attr_groups);
	aoedisk_add_debugfs(d);

	spin_lock_irqsave(&d->lock, flags);
	WARN_ON(!(d->flags & DEVFL_GD_NOW));
	d->flags &= ~DEVFL_GD_NOW;
	spin_unlock_irqrestore(&d->lock, flags);
	वापस;

err_mempool:
	mempool_destroy(mp);
err_disk:
	put_disk(gd);
err:
	spin_lock_irqsave(&d->lock, flags);
	d->flags &= ~DEVFL_GD_NOW;
	schedule_work(&d->work);
	spin_unlock_irqrestore(&d->lock, flags);
पूर्ण

व्योम
aoeblk_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(aoe_debugfs_dir);
	aoe_debugfs_dir = शून्य;
	kmem_cache_destroy(buf_pool_cache);
पूर्ण

पूर्णांक __init
aoeblk_init(व्योम)
अणु
	buf_pool_cache = kmem_cache_create("aoe_bufs",
					   माप(काष्ठा buf),
					   0, 0, शून्य);
	अगर (buf_pool_cache == शून्य)
		वापस -ENOMEM;
	aoe_debugfs_dir = debugfs_create_dir("aoe", शून्य);
	वापस 0;
पूर्ण

