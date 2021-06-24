<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*  Xenbus code क्रम blkअगर backend
    Copyright (C) 2005 Rusty Russell <rusty@rustcorp.com.au>
    Copyright (C) 2005 XenSource Ltd


*/

#घोषणा pr_fmt(fmt) "xen-blkback: " fmt

#समावेश <मानकतर्क.स>
#समावेश <linux/module.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <xen/events.h>
#समावेश <xen/grant_table.h>
#समावेश "common.h"

/* On the XenBus the max length of 'ring-ref%u'. */
#घोषणा RINGREF_NAME_LEN (20)

काष्ठा backend_info अणु
	काष्ठा xenbus_device	*dev;
	काष्ठा xen_blkअगर	*blkअगर;
	काष्ठा xenbus_watch	backend_watch;
	अचिन्हित		major;
	अचिन्हित		minor;
	अक्षर			*mode;
पूर्ण;

अटल काष्ठा kmem_cache *xen_blkअगर_cachep;
अटल व्योम connect(काष्ठा backend_info *);
अटल पूर्णांक connect_ring(काष्ठा backend_info *);
अटल व्योम backend_changed(काष्ठा xenbus_watch *, स्थिर अक्षर *,
			    स्थिर अक्षर *);
अटल व्योम xen_blkअगर_मुक्त(काष्ठा xen_blkअगर *blkअगर);
अटल व्योम xen_vbd_मुक्त(काष्ठा xen_vbd *vbd);

काष्ठा xenbus_device *xen_blkbk_xenbus(काष्ठा backend_info *be)
अणु
	वापस be->dev;
पूर्ण

/*
 * The last request could मुक्त the device from softirq context and
 * xen_blkअगर_मुक्त() can sleep.
 */
अटल व्योम xen_blkअगर_deferred_मुक्त(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा xen_blkअगर *blkअगर;

	blkअगर = container_of(work, काष्ठा xen_blkअगर, मुक्त_work);
	xen_blkअगर_मुक्त(blkअगर);
पूर्ण

अटल पूर्णांक blkback_name(काष्ठा xen_blkअगर *blkअगर, अक्षर *buf)
अणु
	अक्षर *devpath, *devname;
	काष्ठा xenbus_device *dev = blkअगर->be->dev;

	devpath = xenbus_पढ़ो(XBT_NIL, dev->nodename, "dev", शून्य);
	अगर (IS_ERR(devpath))
		वापस PTR_ERR(devpath);

	devname = म_माला(devpath, "/dev/");
	अगर (devname != शून्य)
		devname += म_माप("/dev/");
	अन्यथा
		devname  = devpath;

	snम_लिखो(buf, TASK_COMM_LEN, "%d.%s", blkअगर->करोmid, devname);
	kमुक्त(devpath);

	वापस 0;
पूर्ण

अटल व्योम xen_update_blkअगर_status(काष्ठा xen_blkअगर *blkअगर)
अणु
	पूर्णांक err;
	अक्षर name[TASK_COMM_LEN];
	काष्ठा xen_blkअगर_ring *ring;
	पूर्णांक i;

	/* Not पढ़ोy to connect? */
	अगर (!blkअगर->rings || !blkअगर->rings[0].irq || !blkअगर->vbd.bdev)
		वापस;

	/* Alपढ़ोy connected? */
	अगर (blkअगर->be->dev->state == XenbusStateConnected)
		वापस;

	/* Attempt to connect: निकास अगर we fail to. */
	connect(blkअगर->be);
	अगर (blkअगर->be->dev->state != XenbusStateConnected)
		वापस;

	err = blkback_name(blkअगर, name);
	अगर (err) अणु
		xenbus_dev_error(blkअगर->be->dev, err, "get blkback dev name");
		वापस;
	पूर्ण

	err = filemap_ग_लिखो_and_रुको(blkअगर->vbd.bdev->bd_inode->i_mapping);
	अगर (err) अणु
		xenbus_dev_error(blkअगर->be->dev, err, "block flush");
		वापस;
	पूर्ण
	invalidate_inode_pages2(blkअगर->vbd.bdev->bd_inode->i_mapping);

	क्रम (i = 0; i < blkअगर->nr_rings; i++) अणु
		ring = &blkअगर->rings[i];
		ring->xenblkd = kthपढ़ो_run(xen_blkअगर_schedule, ring, "%s-%d", name, i);
		अगर (IS_ERR(ring->xenblkd)) अणु
			err = PTR_ERR(ring->xenblkd);
			ring->xenblkd = शून्य;
			xenbus_dev_fatal(blkअगर->be->dev, err,
					"start %s-%d xenblkd", name, i);
			जाओ out;
		पूर्ण
	पूर्ण
	वापस;

out:
	जबतक (--i >= 0) अणु
		ring = &blkअगर->rings[i];
		kthपढ़ो_stop(ring->xenblkd);
	पूर्ण
	वापस;
पूर्ण

अटल पूर्णांक xen_blkअगर_alloc_rings(काष्ठा xen_blkअगर *blkअगर)
अणु
	अचिन्हित पूर्णांक r;

	blkअगर->rings = kसुस्मृति(blkअगर->nr_rings, माप(काष्ठा xen_blkअगर_ring),
			       GFP_KERNEL);
	अगर (!blkअगर->rings)
		वापस -ENOMEM;

	क्रम (r = 0; r < blkअगर->nr_rings; r++) अणु
		काष्ठा xen_blkअगर_ring *ring = &blkअगर->rings[r];

		spin_lock_init(&ring->blk_ring_lock);
		init_रुकोqueue_head(&ring->wq);
		INIT_LIST_HEAD(&ring->pending_मुक्त);
		INIT_LIST_HEAD(&ring->persistent_purge_list);
		INIT_WORK(&ring->persistent_purge_work, xen_blkbk_unmap_purged_grants);
		gnttab_page_cache_init(&ring->मुक्त_pages);

		spin_lock_init(&ring->pending_मुक्त_lock);
		init_रुकोqueue_head(&ring->pending_मुक्त_wq);
		init_रुकोqueue_head(&ring->shutकरोwn_wq);
		ring->blkअगर = blkअगर;
		ring->st_prपूर्णांक = jअगरfies;
		ring->active = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा xen_blkअगर *xen_blkअगर_alloc(करोmid_t करोmid)
अणु
	काष्ठा xen_blkअगर *blkअगर;

	BUILD_BUG_ON(MAX_INसूचीECT_PAGES > BLKIF_MAX_INसूचीECT_PAGES_PER_REQUEST);

	blkअगर = kmem_cache_zalloc(xen_blkअगर_cachep, GFP_KERNEL);
	अगर (!blkअगर)
		वापस ERR_PTR(-ENOMEM);

	blkअगर->करोmid = करोmid;
	atomic_set(&blkअगर->refcnt, 1);
	init_completion(&blkअगर->drain_complete);

	/*
	 * Because मुक्तing back to the cache may be deferred, it is not
	 * safe to unload the module (and hence destroy the cache) until
	 * this has completed. To prevent premature unloading, take an
	 * extra module reference here and release only when the object
	 * has been मुक्तd back to the cache.
	 */
	__module_get(THIS_MODULE);
	INIT_WORK(&blkअगर->मुक्त_work, xen_blkअगर_deferred_मुक्त);

	वापस blkअगर;
पूर्ण

अटल पूर्णांक xen_blkअगर_map(काष्ठा xen_blkअगर_ring *ring, grant_ref_t *gref,
			 अचिन्हित पूर्णांक nr_grefs, अचिन्हित पूर्णांक evtchn)
अणु
	पूर्णांक err;
	काष्ठा xen_blkअगर *blkअगर = ring->blkअगर;
	स्थिर काष्ठा blkअगर_common_sring *sring_common;
	RING_IDX rsp_prod, req_prod;
	अचिन्हित पूर्णांक size;

	/* Alपढ़ोy connected through? */
	अगर (ring->irq)
		वापस 0;

	err = xenbus_map_ring_valloc(blkअगर->be->dev, gref, nr_grefs,
				     &ring->blk_ring);
	अगर (err < 0)
		वापस err;

	sring_common = (काष्ठा blkअगर_common_sring *)ring->blk_ring;
	rsp_prod = READ_ONCE(sring_common->rsp_prod);
	req_prod = READ_ONCE(sring_common->req_prod);

	चयन (blkअगर->blk_protocol) अणु
	हाल BLKIF_PROTOCOL_NATIVE:
	अणु
		काष्ठा blkअगर_sring *sring_native =
			(काष्ठा blkअगर_sring *)ring->blk_ring;

		BACK_RING_ATTACH(&ring->blk_rings.native, sring_native,
				 rsp_prod, XEN_PAGE_SIZE * nr_grefs);
		size = __RING_SIZE(sring_native, XEN_PAGE_SIZE * nr_grefs);
		अवरोध;
	पूर्ण
	हाल BLKIF_PROTOCOL_X86_32:
	अणु
		काष्ठा blkअगर_x86_32_sring *sring_x86_32 =
			(काष्ठा blkअगर_x86_32_sring *)ring->blk_ring;

		BACK_RING_ATTACH(&ring->blk_rings.x86_32, sring_x86_32,
				 rsp_prod, XEN_PAGE_SIZE * nr_grefs);
		size = __RING_SIZE(sring_x86_32, XEN_PAGE_SIZE * nr_grefs);
		अवरोध;
	पूर्ण
	हाल BLKIF_PROTOCOL_X86_64:
	अणु
		काष्ठा blkअगर_x86_64_sring *sring_x86_64 =
			(काष्ठा blkअगर_x86_64_sring *)ring->blk_ring;

		BACK_RING_ATTACH(&ring->blk_rings.x86_64, sring_x86_64,
				 rsp_prod, XEN_PAGE_SIZE * nr_grefs);
		size = __RING_SIZE(sring_x86_64, XEN_PAGE_SIZE * nr_grefs);
		अवरोध;
	पूर्ण
	शेष:
		BUG();
	पूर्ण

	err = -EIO;
	अगर (req_prod - rsp_prod > size)
		जाओ fail;

	err = bind_पूर्णांकerकरोमुख्य_evtchn_to_irqhandler_lateeoi(blkअगर->be->dev,
			evtchn, xen_blkअगर_be_पूर्णांक, 0, "blkif-backend", ring);
	अगर (err < 0)
		जाओ fail;
	ring->irq = err;

	वापस 0;

fail:
	xenbus_unmap_ring_vमुक्त(blkअगर->be->dev, ring->blk_ring);
	ring->blk_rings.common.sring = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक xen_blkअगर_disconnect(काष्ठा xen_blkअगर *blkअगर)
अणु
	काष्ठा pending_req *req, *n;
	अचिन्हित पूर्णांक j, r;
	bool busy = false;

	क्रम (r = 0; r < blkअगर->nr_rings; r++) अणु
		काष्ठा xen_blkअगर_ring *ring = &blkअगर->rings[r];
		अचिन्हित पूर्णांक i = 0;

		अगर (!ring->active)
			जारी;

		अगर (ring->xenblkd) अणु
			kthपढ़ो_stop(ring->xenblkd);
			ring->xenblkd = शून्य;
			wake_up(&ring->shutकरोwn_wq);
		पूर्ण

		/* The above kthपढ़ो_stop() guarantees that at this poपूर्णांक we
		 * करोn't have any discard_io or other_io requests. So, checking
		 * क्रम inflight IO is enough.
		 */
		अगर (atomic_पढ़ो(&ring->inflight) > 0) अणु
			busy = true;
			जारी;
		पूर्ण

		अगर (ring->irq) अणु
			unbind_from_irqhandler(ring->irq, ring);
			ring->irq = 0;
		पूर्ण

		अगर (ring->blk_rings.common.sring) अणु
			xenbus_unmap_ring_vमुक्त(blkअगर->be->dev, ring->blk_ring);
			ring->blk_rings.common.sring = शून्य;
		पूर्ण

		/* Remove all persistent grants and the cache of ballooned pages. */
		xen_blkbk_मुक्त_caches(ring);

		/* Check that there is no request in use */
		list_क्रम_each_entry_safe(req, n, &ring->pending_मुक्त, मुक्त_list) अणु
			list_del(&req->मुक्त_list);

			क्रम (j = 0; j < MAX_INसूचीECT_SEGMENTS; j++)
				kमुक्त(req->segments[j]);

			क्रम (j = 0; j < MAX_INसूचीECT_PAGES; j++)
				kमुक्त(req->indirect_pages[j]);

			kमुक्त(req);
			i++;
		पूर्ण

		BUG_ON(atomic_पढ़ो(&ring->persistent_gnt_in_use) != 0);
		BUG_ON(!list_empty(&ring->persistent_purge_list));
		BUG_ON(!RB_EMPTY_ROOT(&ring->persistent_gnts));
		BUG_ON(ring->मुक्त_pages.num_pages != 0);
		BUG_ON(ring->persistent_gnt_c != 0);
		WARN_ON(i != (XEN_BLKIF_REQS_PER_PAGE * blkअगर->nr_ring_pages));
		ring->active = false;
	पूर्ण
	अगर (busy)
		वापस -EBUSY;

	blkअगर->nr_ring_pages = 0;
	/*
	 * blkअगर->rings was allocated in connect_ring, so we should मुक्त it in
	 * here.
	 */
	kमुक्त(blkअगर->rings);
	blkअगर->rings = शून्य;
	blkअगर->nr_rings = 0;

	वापस 0;
पूर्ण

अटल व्योम xen_blkअगर_मुक्त(काष्ठा xen_blkअगर *blkअगर)
अणु
	WARN_ON(xen_blkअगर_disconnect(blkअगर));
	xen_vbd_मुक्त(&blkअगर->vbd);
	kमुक्त(blkअगर->be->mode);
	kमुक्त(blkअगर->be);

	/* Make sure everything is drained beक्रमe shutting करोwn */
	kmem_cache_मुक्त(xen_blkअगर_cachep, blkअगर);
	module_put(THIS_MODULE);
पूर्ण

पूर्णांक __init xen_blkअगर_पूर्णांकerface_init(व्योम)
अणु
	xen_blkअगर_cachep = kmem_cache_create("blkif_cache",
					     माप(काष्ठा xen_blkअगर),
					     0, 0, शून्य);
	अगर (!xen_blkअगर_cachep)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम xen_blkअगर_पूर्णांकerface_fini(व्योम)
अणु
	kmem_cache_destroy(xen_blkअगर_cachep);
	xen_blkअगर_cachep = शून्य;
पूर्ण

/*
 *  sysfs पूर्णांकerface क्रम VBD I/O requests
 */

#घोषणा VBD_SHOW_ALLRING(name, क्रमmat)					\
	अटल sमाप_प्रकार show_##name(काष्ठा device *_dev,			\
				   काष्ठा device_attribute *attr,	\
				   अक्षर *buf)				\
	अणु								\
		काष्ठा xenbus_device *dev = to_xenbus_device(_dev);	\
		काष्ठा backend_info *be = dev_get_drvdata(&dev->dev);	\
		काष्ठा xen_blkअगर *blkअगर = be->blkअगर;			\
		अचिन्हित पूर्णांक i;						\
		अचिन्हित दीर्घ दीर्घ result = 0;				\
									\
		अगर (!blkअगर->rings)				\
			जाओ out;					\
									\
		क्रम (i = 0; i < blkअगर->nr_rings; i++) अणु		\
			काष्ठा xen_blkअगर_ring *ring = &blkअगर->rings[i];	\
									\
			result += ring->st_##name;			\
		पूर्ण							\
									\
out:									\
		वापस प्र_लिखो(buf, क्रमmat, result);			\
	पूर्ण								\
	अटल DEVICE_ATTR(name, 0444, show_##name, शून्य)

VBD_SHOW_ALLRING(oo_req,  "%llu\n");
VBD_SHOW_ALLRING(rd_req,  "%llu\n");
VBD_SHOW_ALLRING(wr_req,  "%llu\n");
VBD_SHOW_ALLRING(f_req,  "%llu\n");
VBD_SHOW_ALLRING(ds_req,  "%llu\n");
VBD_SHOW_ALLRING(rd_sect, "%llu\n");
VBD_SHOW_ALLRING(wr_sect, "%llu\n");

अटल काष्ठा attribute *xen_vbdstat_attrs[] = अणु
	&dev_attr_oo_req.attr,
	&dev_attr_rd_req.attr,
	&dev_attr_wr_req.attr,
	&dev_attr_f_req.attr,
	&dev_attr_ds_req.attr,
	&dev_attr_rd_sect.attr,
	&dev_attr_wr_sect.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group xen_vbdstat_group = अणु
	.name = "statistics",
	.attrs = xen_vbdstat_attrs,
पूर्ण;

#घोषणा VBD_SHOW(name, क्रमmat, args...)					\
	अटल sमाप_प्रकार show_##name(काष्ठा device *_dev,			\
				   काष्ठा device_attribute *attr,	\
				   अक्षर *buf)				\
	अणु								\
		काष्ठा xenbus_device *dev = to_xenbus_device(_dev);	\
		काष्ठा backend_info *be = dev_get_drvdata(&dev->dev);	\
									\
		वापस प्र_लिखो(buf, क्रमmat, ##args);			\
	पूर्ण								\
	अटल DEVICE_ATTR(name, 0444, show_##name, शून्य)

VBD_SHOW(physical_device, "%x:%x\n", be->major, be->minor);
VBD_SHOW(mode, "%s\n", be->mode);

अटल पूर्णांक xenvbd_sysfs_addअगर(काष्ठा xenbus_device *dev)
अणु
	पूर्णांक error;

	error = device_create_file(&dev->dev, &dev_attr_physical_device);
	अगर (error)
		जाओ fail1;

	error = device_create_file(&dev->dev, &dev_attr_mode);
	अगर (error)
		जाओ fail2;

	error = sysfs_create_group(&dev->dev.kobj, &xen_vbdstat_group);
	अगर (error)
		जाओ fail3;

	वापस 0;

fail3:	sysfs_हटाओ_group(&dev->dev.kobj, &xen_vbdstat_group);
fail2:	device_हटाओ_file(&dev->dev, &dev_attr_mode);
fail1:	device_हटाओ_file(&dev->dev, &dev_attr_physical_device);
	वापस error;
पूर्ण

अटल व्योम xenvbd_sysfs_delअगर(काष्ठा xenbus_device *dev)
अणु
	sysfs_हटाओ_group(&dev->dev.kobj, &xen_vbdstat_group);
	device_हटाओ_file(&dev->dev, &dev_attr_mode);
	device_हटाओ_file(&dev->dev, &dev_attr_physical_device);
पूर्ण

अटल व्योम xen_vbd_मुक्त(काष्ठा xen_vbd *vbd)
अणु
	अगर (vbd->bdev)
		blkdev_put(vbd->bdev, vbd->पढ़ोonly ? FMODE_READ : FMODE_WRITE);
	vbd->bdev = शून्य;
पूर्ण

/* Enable the persistent grants feature. */
अटल bool feature_persistent = true;
module_param(feature_persistent, bool, 0644);
MODULE_PARM_DESC(feature_persistent,
		"Enables the persistent grants feature");

अटल पूर्णांक xen_vbd_create(काष्ठा xen_blkअगर *blkअगर, blkअगर_vdev_t handle,
			  अचिन्हित major, अचिन्हित minor, पूर्णांक पढ़ोonly,
			  पूर्णांक cdrom)
अणु
	काष्ठा xen_vbd *vbd;
	काष्ठा block_device *bdev;
	काष्ठा request_queue *q;

	vbd = &blkअगर->vbd;
	vbd->handle   = handle;
	vbd->पढ़ोonly = पढ़ोonly;
	vbd->type     = 0;

	vbd->pdevice  = MKDEV(major, minor);

	bdev = blkdev_get_by_dev(vbd->pdevice, vbd->पढ़ोonly ?
				 FMODE_READ : FMODE_WRITE, शून्य);

	अगर (IS_ERR(bdev)) अणु
		pr_warn("xen_vbd_create: device %08x could not be opened\n",
			vbd->pdevice);
		वापस -ENOENT;
	पूर्ण

	vbd->bdev = bdev;
	अगर (vbd->bdev->bd_disk == शून्य) अणु
		pr_warn("xen_vbd_create: device %08x doesn't exist\n",
			vbd->pdevice);
		xen_vbd_मुक्त(vbd);
		वापस -ENOENT;
	पूर्ण
	vbd->size = vbd_sz(vbd);

	अगर (vbd->bdev->bd_disk->flags & GENHD_FL_CD || cdrom)
		vbd->type |= VDISK_CDROM;
	अगर (vbd->bdev->bd_disk->flags & GENHD_FL_REMOVABLE)
		vbd->type |= VDISK_REMOVABLE;

	q = bdev_get_queue(bdev);
	अगर (q && test_bit(QUEUE_FLAG_WC, &q->queue_flags))
		vbd->flush_support = true;

	अगर (q && blk_queue_secure_erase(q))
		vbd->discard_secure = true;

	vbd->feature_gnt_persistent = feature_persistent;

	pr_debug("Successful creation of handle=%04x (dom=%u)\n",
		handle, blkअगर->करोmid);
	वापस 0;
पूर्ण

अटल पूर्णांक xen_blkbk_हटाओ(काष्ठा xenbus_device *dev)
अणु
	काष्ठा backend_info *be = dev_get_drvdata(&dev->dev);

	pr_debug("%s %p %d\n", __func__, dev, dev->otherend_id);

	अगर (be->major || be->minor)
		xenvbd_sysfs_delअगर(dev);

	अगर (be->backend_watch.node) अणु
		unरेजिस्टर_xenbus_watch(&be->backend_watch);
		kमुक्त(be->backend_watch.node);
		be->backend_watch.node = शून्य;
	पूर्ण

	dev_set_drvdata(&dev->dev, शून्य);

	अगर (be->blkअगर) अणु
		xen_blkअगर_disconnect(be->blkअगर);

		/* Put the reference we set in xen_blkअगर_alloc(). */
		xen_blkअगर_put(be->blkअगर);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक xen_blkbk_flush_diskcache(काष्ठा xenbus_transaction xbt,
			      काष्ठा backend_info *be, पूर्णांक state)
अणु
	काष्ठा xenbus_device *dev = be->dev;
	पूर्णांक err;

	err = xenbus_म_लिखो(xbt, dev->nodename, "feature-flush-cache",
			    "%d", state);
	अगर (err)
		dev_warn(&dev->dev, "writing feature-flush-cache (%d)", err);

	वापस err;
पूर्ण

अटल व्योम xen_blkbk_discard(काष्ठा xenbus_transaction xbt, काष्ठा backend_info *be)
अणु
	काष्ठा xenbus_device *dev = be->dev;
	काष्ठा xen_blkअगर *blkअगर = be->blkअगर;
	पूर्णांक err;
	पूर्णांक state = 0;
	काष्ठा block_device *bdev = be->blkअगर->vbd.bdev;
	काष्ठा request_queue *q = bdev_get_queue(bdev);

	अगर (!xenbus_पढ़ो_अचिन्हित(dev->nodename, "discard-enable", 1))
		वापस;

	अगर (blk_queue_discard(q)) अणु
		err = xenbus_म_लिखो(xbt, dev->nodename,
			"discard-granularity", "%u",
			q->limits.discard_granularity);
		अगर (err) अणु
			dev_warn(&dev->dev, "writing discard-granularity (%d)", err);
			वापस;
		पूर्ण
		err = xenbus_म_लिखो(xbt, dev->nodename,
			"discard-alignment", "%u",
			q->limits.discard_alignment);
		अगर (err) अणु
			dev_warn(&dev->dev, "writing discard-alignment (%d)", err);
			वापस;
		पूर्ण
		state = 1;
		/* Optional. */
		err = xenbus_म_लिखो(xbt, dev->nodename,
				    "discard-secure", "%d",
				    blkअगर->vbd.discard_secure);
		अगर (err) अणु
			dev_warn(&dev->dev, "writing discard-secure (%d)", err);
			वापस;
		पूर्ण
	पूर्ण
	err = xenbus_म_लिखो(xbt, dev->nodename, "feature-discard",
			    "%d", state);
	अगर (err)
		dev_warn(&dev->dev, "writing feature-discard (%d)", err);
पूर्ण

पूर्णांक xen_blkbk_barrier(काष्ठा xenbus_transaction xbt,
		      काष्ठा backend_info *be, पूर्णांक state)
अणु
	काष्ठा xenbus_device *dev = be->dev;
	पूर्णांक err;

	err = xenbus_म_लिखो(xbt, dev->nodename, "feature-barrier",
			    "%d", state);
	अगर (err)
		dev_warn(&dev->dev, "writing feature-barrier (%d)", err);

	वापस err;
पूर्ण

/*
 * Entry poपूर्णांक to this code when a new device is created.  Allocate the basic
 * काष्ठाures, and watch the store रुकोing क्रम the hotplug scripts to tell us
 * the device's physical major and minor numbers.  Switch to InitWait.
 */
अटल पूर्णांक xen_blkbk_probe(काष्ठा xenbus_device *dev,
			   स्थिर काष्ठा xenbus_device_id *id)
अणु
	पूर्णांक err;
	काष्ठा backend_info *be = kzalloc(माप(काष्ठा backend_info),
					  GFP_KERNEL);

	/* match the pr_debug in xen_blkbk_हटाओ */
	pr_debug("%s %p %d\n", __func__, dev, dev->otherend_id);

	अगर (!be) अणु
		xenbus_dev_fatal(dev, -ENOMEM,
				 "allocating backend structure");
		वापस -ENOMEM;
	पूर्ण
	be->dev = dev;
	dev_set_drvdata(&dev->dev, be);

	be->blkअगर = xen_blkअगर_alloc(dev->otherend_id);
	अगर (IS_ERR(be->blkअगर)) अणु
		err = PTR_ERR(be->blkअगर);
		be->blkअगर = शून्य;
		xenbus_dev_fatal(dev, err, "creating block interface");
		जाओ fail;
	पूर्ण

	err = xenbus_म_लिखो(XBT_NIL, dev->nodename,
			    "feature-max-indirect-segments", "%u",
			    MAX_INसूचीECT_SEGMENTS);
	अगर (err)
		dev_warn(&dev->dev,
			 "writing %s/feature-max-indirect-segments (%d)",
			 dev->nodename, err);

	/* Multi-queue: advertise how many queues are supported by us.*/
	err = xenbus_म_लिखो(XBT_NIL, dev->nodename,
			    "multi-queue-max-queues", "%u", xenblk_max_queues);
	अगर (err)
		pr_warn("Error writing multi-queue-max-queues\n");

	/* setup back poपूर्णांकer */
	be->blkअगर->be = be;

	err = xenbus_watch_pathfmt(dev, &be->backend_watch, शून्य,
				   backend_changed,
				   "%s/%s", dev->nodename, "physical-device");
	अगर (err)
		जाओ fail;

	err = xenbus_म_लिखो(XBT_NIL, dev->nodename, "max-ring-page-order", "%u",
			    xen_blkअगर_max_ring_order);
	अगर (err)
		pr_warn("%s write out 'max-ring-page-order' failed\n", __func__);

	err = xenbus_चयन_state(dev, XenbusStateInitWait);
	अगर (err)
		जाओ fail;

	वापस 0;

fail:
	pr_warn("%s failed\n", __func__);
	xen_blkbk_हटाओ(dev);
	वापस err;
पूर्ण

/*
 * Callback received when the hotplug scripts have placed the physical-device
 * node.  Read it and the mode node, and create a vbd.  If the frontend is
 * पढ़ोy, connect.
 */
अटल व्योम backend_changed(काष्ठा xenbus_watch *watch,
			    स्थिर अक्षर *path, स्थिर अक्षर *token)
अणु
	पूर्णांक err;
	अचिन्हित major;
	अचिन्हित minor;
	काष्ठा backend_info *be
		= container_of(watch, काष्ठा backend_info, backend_watch);
	काष्ठा xenbus_device *dev = be->dev;
	पूर्णांक cdrom = 0;
	अचिन्हित दीर्घ handle;
	अक्षर *device_type;

	pr_debug("%s %p %d\n", __func__, dev, dev->otherend_id);

	err = xenbus_म_पूछो(XBT_NIL, dev->nodename, "physical-device", "%x:%x",
			   &major, &minor);
	अगर (XENBUS_EXIST_ERR(err)) अणु
		/*
		 * Since this watch will fire once immediately after it is
		 * रेजिस्टरed, we expect this.  Ignore it, and रुको क्रम the
		 * hotplug scripts.
		 */
		वापस;
	पूर्ण
	अगर (err != 2) अणु
		xenbus_dev_fatal(dev, err, "reading physical-device");
		वापस;
	पूर्ण

	अगर (be->major | be->minor) अणु
		अगर (be->major != major || be->minor != minor)
			pr_warn("changing physical device (from %x:%x to %x:%x) not supported.\n",
				be->major, be->minor, major, minor);
		वापस;
	पूर्ण

	be->mode = xenbus_पढ़ो(XBT_NIL, dev->nodename, "mode", शून्य);
	अगर (IS_ERR(be->mode)) अणु
		err = PTR_ERR(be->mode);
		be->mode = शून्य;
		xenbus_dev_fatal(dev, err, "reading mode");
		वापस;
	पूर्ण

	device_type = xenbus_पढ़ो(XBT_NIL, dev->otherend, "device-type", शून्य);
	अगर (!IS_ERR(device_type)) अणु
		cdrom = म_भेद(device_type, "cdrom") == 0;
		kमुक्त(device_type);
	पूर्ण

	/* Front end dir is a number, which is used as the handle. */
	err = kम_से_अदीर्घ(म_खोजप(dev->otherend, '/') + 1, 0, &handle);
	अगर (err) अणु
		kमुक्त(be->mode);
		be->mode = शून्य;
		वापस;
	पूर्ण

	be->major = major;
	be->minor = minor;

	err = xen_vbd_create(be->blkअगर, handle, major, minor,
			     !म_अक्षर(be->mode, 'w'), cdrom);

	अगर (err)
		xenbus_dev_fatal(dev, err, "creating vbd structure");
	अन्यथा अणु
		err = xenvbd_sysfs_addअगर(dev);
		अगर (err) अणु
			xen_vbd_मुक्त(&be->blkअगर->vbd);
			xenbus_dev_fatal(dev, err, "creating sysfs entries");
		पूर्ण
	पूर्ण

	अगर (err) अणु
		kमुक्त(be->mode);
		be->mode = शून्य;
		be->major = 0;
		be->minor = 0;
	पूर्ण अन्यथा अणु
		/* We're potentially connected now */
		xen_update_blkअगर_status(be->blkअगर);
	पूर्ण
पूर्ण

/*
 * Callback received when the frontend's state changes.
 */
अटल व्योम frontend_changed(काष्ठा xenbus_device *dev,
			     क्रमागत xenbus_state frontend_state)
अणु
	काष्ठा backend_info *be = dev_get_drvdata(&dev->dev);
	पूर्णांक err;

	pr_debug("%s %p %s\n", __func__, dev, xenbus_strstate(frontend_state));

	चयन (frontend_state) अणु
	हाल XenbusStateInitialising:
		अगर (dev->state == XenbusStateClosed) अणु
			pr_info("%s: prepare for reconnect\n", dev->nodename);
			xenbus_चयन_state(dev, XenbusStateInitWait);
		पूर्ण
		अवरोध;

	हाल XenbusStateInitialised:
	हाल XenbusStateConnected:
		/*
		 * Ensure we connect even when two watches fire in
		 * बंद succession and we miss the पूर्णांकermediate value
		 * of frontend_state.
		 */
		अगर (dev->state == XenbusStateConnected)
			अवरोध;

		/*
		 * Enक्रमce precondition beक्रमe potential leak poपूर्णांक.
		 * xen_blkअगर_disconnect() is idempotent.
		 */
		err = xen_blkअगर_disconnect(be->blkअगर);
		अगर (err) अणु
			xenbus_dev_fatal(dev, err, "pending I/O");
			अवरोध;
		पूर्ण

		err = connect_ring(be);
		अगर (err) अणु
			/*
			 * Clean up so that memory resources can be used by
			 * other devices. connect_ring reported alपढ़ोy error.
			 */
			xen_blkअगर_disconnect(be->blkअगर);
			अवरोध;
		पूर्ण
		xen_update_blkअगर_status(be->blkअगर);
		अवरोध;

	हाल XenbusStateClosing:
		xenbus_चयन_state(dev, XenbusStateClosing);
		अवरोध;

	हाल XenbusStateClosed:
		xen_blkअगर_disconnect(be->blkअगर);
		xenbus_चयन_state(dev, XenbusStateClosed);
		अगर (xenbus_dev_is_online(dev))
			अवरोध;
		fallthrough;
		/* अगर not online */
	हाल XenbusStateUnknown:
		/* implies xen_blkअगर_disconnect() via xen_blkbk_हटाओ() */
		device_unरेजिस्टर(&dev->dev);
		अवरोध;

	शेष:
		xenbus_dev_fatal(dev, -EINVAL, "saw state %d at frontend",
				 frontend_state);
		अवरोध;
	पूर्ण
पूर्ण

/* Once a memory pressure is detected, squeeze मुक्त page pools क्रम a जबतक. */
अटल अचिन्हित पूर्णांक buffer_squeeze_duration_ms = 10;
module_param_named(buffer_squeeze_duration_ms,
		buffer_squeeze_duration_ms, पूर्णांक, 0644);
MODULE_PARM_DESC(buffer_squeeze_duration_ms,
"Duration in ms to squeeze pages buffer when a memory pressure is detected");

/*
 * Callback received when the memory pressure is detected.
 */
अटल व्योम reclaim_memory(काष्ठा xenbus_device *dev)
अणु
	काष्ठा backend_info *be = dev_get_drvdata(&dev->dev);

	अगर (!be)
		वापस;
	be->blkअगर->buffer_squeeze_end = jअगरfies +
		msecs_to_jअगरfies(buffer_squeeze_duration_ms);
पूर्ण

/* ** Connection ** */

/*
 * Write the physical details regarding the block device to the store, and
 * चयन to Connected state.
 */
अटल व्योम connect(काष्ठा backend_info *be)
अणु
	काष्ठा xenbus_transaction xbt;
	पूर्णांक err;
	काष्ठा xenbus_device *dev = be->dev;

	pr_debug("%s %s\n", __func__, dev->otherend);

	/* Supply the inक्रमmation about the device the frontend needs */
again:
	err = xenbus_transaction_start(&xbt);
	अगर (err) अणु
		xenbus_dev_fatal(dev, err, "starting transaction");
		वापस;
	पूर्ण

	/* If we can't advertise it is OK. */
	xen_blkbk_flush_diskcache(xbt, be, be->blkअगर->vbd.flush_support);

	xen_blkbk_discard(xbt, be);

	xen_blkbk_barrier(xbt, be, be->blkअगर->vbd.flush_support);

	err = xenbus_म_लिखो(xbt, dev->nodename, "feature-persistent", "%u",
			be->blkअगर->vbd.feature_gnt_persistent);
	अगर (err) अणु
		xenbus_dev_fatal(dev, err, "writing %s/feature-persistent",
				 dev->nodename);
		जाओ पात;
	पूर्ण

	err = xenbus_म_लिखो(xbt, dev->nodename, "sectors", "%llu",
			    (अचिन्हित दीर्घ दीर्घ)vbd_sz(&be->blkअगर->vbd));
	अगर (err) अणु
		xenbus_dev_fatal(dev, err, "writing %s/sectors",
				 dev->nodename);
		जाओ पात;
	पूर्ण

	/* FIXME: use a typename instead */
	err = xenbus_म_लिखो(xbt, dev->nodename, "info", "%u",
			    be->blkअगर->vbd.type |
			    (be->blkअगर->vbd.पढ़ोonly ? VDISK_READONLY : 0));
	अगर (err) अणु
		xenbus_dev_fatal(dev, err, "writing %s/info",
				 dev->nodename);
		जाओ पात;
	पूर्ण
	err = xenbus_म_लिखो(xbt, dev->nodename, "sector-size", "%lu",
			    (अचिन्हित दीर्घ)
			    bdev_logical_block_size(be->blkअगर->vbd.bdev));
	अगर (err) अणु
		xenbus_dev_fatal(dev, err, "writing %s/sector-size",
				 dev->nodename);
		जाओ पात;
	पूर्ण
	err = xenbus_म_लिखो(xbt, dev->nodename, "physical-sector-size", "%u",
			    bdev_physical_block_size(be->blkअगर->vbd.bdev));
	अगर (err)
		xenbus_dev_error(dev, err, "writing %s/physical-sector-size",
				 dev->nodename);

	err = xenbus_transaction_end(xbt, 0);
	अगर (err == -EAGAIN)
		जाओ again;
	अगर (err)
		xenbus_dev_fatal(dev, err, "ending transaction");

	err = xenbus_चयन_state(dev, XenbusStateConnected);
	अगर (err)
		xenbus_dev_fatal(dev, err, "%s: switching to Connected state",
				 dev->nodename);

	वापस;
 पात:
	xenbus_transaction_end(xbt, 1);
पूर्ण

/*
 * Each ring may have multi pages, depends on "ring-page-order".
 */
अटल पूर्णांक पढ़ो_per_ring_refs(काष्ठा xen_blkअगर_ring *ring, स्थिर अक्षर *dir)
अणु
	अचिन्हित पूर्णांक ring_ref[XENBUS_MAX_RING_GRANTS];
	काष्ठा pending_req *req, *n;
	पूर्णांक err, i, j;
	काष्ठा xen_blkअगर *blkअगर = ring->blkअगर;
	काष्ठा xenbus_device *dev = blkअगर->be->dev;
	अचिन्हित पूर्णांक nr_grefs, evtchn;

	err = xenbus_म_पूछो(XBT_NIL, dir, "event-channel", "%u",
			  &evtchn);
	अगर (err != 1) अणु
		err = -EINVAL;
		xenbus_dev_fatal(dev, err, "reading %s/event-channel", dir);
		वापस err;
	पूर्ण

	nr_grefs = blkअगर->nr_ring_pages;

	अगर (unlikely(!nr_grefs)) अणु
		WARN_ON(true);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < nr_grefs; i++) अणु
		अक्षर ring_ref_name[RINGREF_NAME_LEN];

		अगर (blkअगर->multi_ref)
			snम_लिखो(ring_ref_name, RINGREF_NAME_LEN, "ring-ref%u", i);
		अन्यथा अणु
			WARN_ON(i != 0);
			snम_लिखो(ring_ref_name, RINGREF_NAME_LEN, "ring-ref");
		पूर्ण

		err = xenbus_म_पूछो(XBT_NIL, dir, ring_ref_name,
				   "%u", &ring_ref[i]);

		अगर (err != 1) अणु
			err = -EINVAL;
			xenbus_dev_fatal(dev, err, "reading %s/%s",
					 dir, ring_ref_name);
			वापस err;
		पूर्ण
	पूर्ण

	err = -ENOMEM;
	क्रम (i = 0; i < nr_grefs * XEN_BLKIF_REQS_PER_PAGE; i++) अणु
		req = kzalloc(माप(*req), GFP_KERNEL);
		अगर (!req)
			जाओ fail;
		list_add_tail(&req->मुक्त_list, &ring->pending_मुक्त);
		क्रम (j = 0; j < MAX_INसूचीECT_SEGMENTS; j++) अणु
			req->segments[j] = kzalloc(माप(*req->segments[0]), GFP_KERNEL);
			अगर (!req->segments[j])
				जाओ fail;
		पूर्ण
		क्रम (j = 0; j < MAX_INसूचीECT_PAGES; j++) अणु
			req->indirect_pages[j] = kzalloc(माप(*req->indirect_pages[0]),
							 GFP_KERNEL);
			अगर (!req->indirect_pages[j])
				जाओ fail;
		पूर्ण
	पूर्ण

	/* Map the shared frame, irq etc. */
	err = xen_blkअगर_map(ring, ring_ref, nr_grefs, evtchn);
	अगर (err) अणु
		xenbus_dev_fatal(dev, err, "mapping ring-ref port %u", evtchn);
		जाओ fail;
	पूर्ण

	वापस 0;

fail:
	list_क्रम_each_entry_safe(req, n, &ring->pending_मुक्त, मुक्त_list) अणु
		list_del(&req->मुक्त_list);
		क्रम (j = 0; j < MAX_INसूचीECT_SEGMENTS; j++) अणु
			अगर (!req->segments[j])
				अवरोध;
			kमुक्त(req->segments[j]);
		पूर्ण
		क्रम (j = 0; j < MAX_INसूचीECT_PAGES; j++) अणु
			अगर (!req->indirect_pages[j])
				अवरोध;
			kमुक्त(req->indirect_pages[j]);
		पूर्ण
		kमुक्त(req);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक connect_ring(काष्ठा backend_info *be)
अणु
	काष्ठा xenbus_device *dev = be->dev;
	काष्ठा xen_blkअगर *blkअगर = be->blkअगर;
	अक्षर protocol[64] = "";
	पूर्णांक err, i;
	अक्षर *xspath;
	माप_प्रकार xspathsize;
	स्थिर माप_प्रकार xenstore_path_ext_size = 11; /* sufficient क्रम "/queue-NNN" */
	अचिन्हित पूर्णांक requested_num_queues = 0;
	अचिन्हित पूर्णांक ring_page_order;

	pr_debug("%s %s\n", __func__, dev->otherend);

	blkअगर->blk_protocol = BLKIF_PROTOCOL_DEFAULT;
	err = xenbus_म_पूछो(XBT_NIL, dev->otherend, "protocol",
			   "%63s", protocol);
	अगर (err <= 0)
		म_नकल(protocol, "unspecified, assuming default");
	अन्यथा अगर (0 == म_भेद(protocol, XEN_IO_PROTO_ABI_NATIVE))
		blkअगर->blk_protocol = BLKIF_PROTOCOL_NATIVE;
	अन्यथा अगर (0 == म_भेद(protocol, XEN_IO_PROTO_ABI_X86_32))
		blkअगर->blk_protocol = BLKIF_PROTOCOL_X86_32;
	अन्यथा अगर (0 == म_भेद(protocol, XEN_IO_PROTO_ABI_X86_64))
		blkअगर->blk_protocol = BLKIF_PROTOCOL_X86_64;
	अन्यथा अणु
		xenbus_dev_fatal(dev, err, "unknown fe protocol %s", protocol);
		वापस -ENOSYS;
	पूर्ण
	अगर (blkअगर->vbd.feature_gnt_persistent)
		blkअगर->vbd.feature_gnt_persistent =
			xenbus_पढ़ो_अचिन्हित(dev->otherend,
					"feature-persistent", 0);

	blkअगर->vbd.overflow_max_grants = 0;

	/*
	 * Read the number of hardware queues from frontend.
	 */
	requested_num_queues = xenbus_पढ़ो_अचिन्हित(dev->otherend,
						    "multi-queue-num-queues",
						    1);
	अगर (requested_num_queues > xenblk_max_queues
	    || requested_num_queues == 0) अणु
		/* Buggy or malicious guest. */
		xenbus_dev_fatal(dev, err,
				"guest requested %u queues, exceeding the maximum of %u.",
				requested_num_queues, xenblk_max_queues);
		वापस -ENOSYS;
	पूर्ण
	blkअगर->nr_rings = requested_num_queues;
	अगर (xen_blkअगर_alloc_rings(blkअगर))
		वापस -ENOMEM;

	pr_info("%s: using %d queues, protocol %d (%s) %s\n", dev->nodename,
		 blkअगर->nr_rings, blkअगर->blk_protocol, protocol,
		 blkअगर->vbd.feature_gnt_persistent ? "persistent grants" : "");

	err = xenbus_म_पूछो(XBT_NIL, dev->otherend, "ring-page-order", "%u",
			   &ring_page_order);
	अगर (err != 1) अणु
		blkअगर->nr_ring_pages = 1;
		blkअगर->multi_ref = false;
	पूर्ण अन्यथा अगर (ring_page_order <= xen_blkअगर_max_ring_order) अणु
		blkअगर->nr_ring_pages = 1 << ring_page_order;
		blkअगर->multi_ref = true;
	पूर्ण अन्यथा अणु
		err = -EINVAL;
		xenbus_dev_fatal(dev, err,
				 "requested ring page order %d exceed max:%d",
				 ring_page_order,
				 xen_blkअगर_max_ring_order);
		वापस err;
	पूर्ण

	अगर (blkअगर->nr_rings == 1)
		वापस पढ़ो_per_ring_refs(&blkअगर->rings[0], dev->otherend);
	अन्यथा अणु
		xspathsize = म_माप(dev->otherend) + xenstore_path_ext_size;
		xspath = kदो_स्मृति(xspathsize, GFP_KERNEL);
		अगर (!xspath) अणु
			xenbus_dev_fatal(dev, -ENOMEM, "reading ring references");
			वापस -ENOMEM;
		पूर्ण

		क्रम (i = 0; i < blkअगर->nr_rings; i++) अणु
			स_रखो(xspath, 0, xspathsize);
			snम_लिखो(xspath, xspathsize, "%s/queue-%u", dev->otherend, i);
			err = पढ़ो_per_ring_refs(&blkअगर->rings[i], xspath);
			अगर (err) अणु
				kमुक्त(xspath);
				वापस err;
			पूर्ण
		पूर्ण
		kमुक्त(xspath);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा xenbus_device_id xen_blkbk_ids[] = अणु
	अणु "vbd" पूर्ण,
	अणु "" पूर्ण
पूर्ण;

अटल काष्ठा xenbus_driver xen_blkbk_driver = अणु
	.ids  = xen_blkbk_ids,
	.probe = xen_blkbk_probe,
	.हटाओ = xen_blkbk_हटाओ,
	.otherend_changed = frontend_changed,
	.allow_rebind = true,
	.reclaim_memory = reclaim_memory,
पूर्ण;

पूर्णांक xen_blkअगर_xenbus_init(व्योम)
अणु
	वापस xenbus_रेजिस्टर_backend(&xen_blkbk_driver);
पूर्ण

व्योम xen_blkअगर_xenbus_fini(व्योम)
अणु
	xenbus_unरेजिस्टर_driver(&xen_blkbk_driver);
पूर्ण
