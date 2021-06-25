<शैली गुरु>
/*
 * blkfront.c
 *
 * XenLinux भव block device driver.
 *
 * Copyright (c) 2003-2004, Keir Fraser & Steve Hand
 * Modअगरications by Mark A. Williamson are (c) Intel Research Cambridge
 * Copyright (c) 2004, Christian Limpach
 * Copyright (c) 2004, Andrew Warfield
 * Copyright (c) 2005, Christopher Clark
 * Copyright (c) 2005, XenSource Ltd
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/list.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/sched/mm.h>

#समावेश <xen/xen.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/events.h>
#समावेश <xen/page.h>
#समावेश <xen/platक्रमm_pci.h>

#समावेश <xen/पूर्णांकerface/grant_table.h>
#समावेश <xen/पूर्णांकerface/io/blkअगर.h>
#समावेश <xen/पूर्णांकerface/io/protocols.h>

#समावेश <यंत्र/xen/hypervisor.h>

/*
 * The minimal size of segment supported by the block framework is PAGE_SIZE.
 * When Linux is using a dअगरferent page size than Xen, it may not be possible
 * to put all the data in a single segment.
 * This can happen when the backend करोesn't support indirect descriptor and
 * thereक्रमe the maximum amount of data that a request can carry is
 * BLKIF_MAX_SEGMENTS_PER_REQUEST * XEN_PAGE_SIZE = 44KB
 *
 * Note that we only support one extra request. So the Linux page size
 * should be <= ( 2 * BLKIF_MAX_SEGMENTS_PER_REQUEST * XEN_PAGE_SIZE) =
 * 88KB.
 */
#घोषणा HAS_EXTRA_REQ (BLKIF_MAX_SEGMENTS_PER_REQUEST < XEN_PFN_PER_PAGE)

क्रमागत blkअगर_state अणु
	BLKIF_STATE_DISCONNECTED,
	BLKIF_STATE_CONNECTED,
	BLKIF_STATE_SUSPENDED,
पूर्ण;

काष्ठा grant अणु
	grant_ref_t gref;
	काष्ठा page *page;
	काष्ठा list_head node;
पूर्ण;

क्रमागत blk_req_status अणु
	REQ_WAITING,
	REQ_DONE,
	REQ_ERROR,
	REQ_EOPNOTSUPP,
पूर्ण;

काष्ठा blk_shaकरोw अणु
	काष्ठा blkअगर_request req;
	काष्ठा request *request;
	काष्ठा grant **grants_used;
	काष्ठा grant **indirect_grants;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक num_sg;
	क्रमागत blk_req_status status;

	#घोषणा NO_ASSOCIATED_ID ~0UL
	/*
	 * Id of the sibling अगर we ever need 2 requests when handling a
	 * block I/O request
	 */
	अचिन्हित दीर्घ associated_id;
पूर्ण;

काष्ठा blkअगर_req अणु
	blk_status_t	error;
पूर्ण;

अटल अंतरभूत काष्ठा blkअगर_req *blkअगर_req(काष्ठा request *rq)
अणु
	वापस blk_mq_rq_to_pdu(rq);
पूर्ण

अटल DEFINE_MUTEX(blkfront_mutex);
अटल स्थिर काष्ठा block_device_operations xlvbd_block_fops;
अटल काष्ठा delayed_work blkfront_work;
अटल LIST_HEAD(info_list);

/*
 * Maximum number of segments in indirect requests, the actual value used by
 * the frontend driver is the minimum of this value and the value provided
 * by the backend driver.
 */

अटल अचिन्हित पूर्णांक xen_blkअगर_max_segments = 32;
module_param_named(max_indirect_segments, xen_blkअगर_max_segments, uपूर्णांक, 0444);
MODULE_PARM_DESC(max_indirect_segments,
		 "Maximum amount of segments in indirect requests (default is 32)");

अटल अचिन्हित पूर्णांक xen_blkअगर_max_queues = 4;
module_param_named(max_queues, xen_blkअगर_max_queues, uपूर्णांक, 0444);
MODULE_PARM_DESC(max_queues, "Maximum number of hardware queues/rings used per virtual disk");

/*
 * Maximum order of pages to be used क्रम the shared ring between front and
 * backend, 4KB page granularity is used.
 */
अटल अचिन्हित पूर्णांक xen_blkअगर_max_ring_order;
module_param_named(max_ring_page_order, xen_blkअगर_max_ring_order, पूर्णांक, 0444);
MODULE_PARM_DESC(max_ring_page_order, "Maximum order of pages to be used for the shared ring");

#घोषणा BLK_RING_SIZE(info)	\
	__CONST_RING_SIZE(blkअगर, XEN_PAGE_SIZE * (info)->nr_ring_pages)

/*
 * ring-ref%u i=(-1UL) would take 11 अक्षरacters + 'ring-ref' is 8, so 19
 * अक्षरacters are enough. Define to 20 to keep consistent with backend.
 */
#घोषणा RINGREF_NAME_LEN (20)
/*
 * queue-%u would take 7 + 10(अच_पूर्णांक_उच्च) = 17 अक्षरacters.
 */
#घोषणा QUEUE_NAME_LEN (17)

/*
 *  Per-ring info.
 *  Every blkfront device can associate with one or more blkfront_ring_info,
 *  depending on how many hardware queues/rings to be used.
 */
काष्ठा blkfront_ring_info अणु
	/* Lock to protect data in every ring buffer. */
	spinlock_t ring_lock;
	काष्ठा blkअगर_front_ring ring;
	अचिन्हित पूर्णांक ring_ref[XENBUS_MAX_RING_GRANTS];
	अचिन्हित पूर्णांक evtchn, irq;
	काष्ठा work_काष्ठा work;
	काष्ठा gnttab_मुक्त_callback callback;
	काष्ठा list_head indirect_pages;
	काष्ठा list_head grants;
	अचिन्हित पूर्णांक persistent_gnts_c;
	अचिन्हित दीर्घ shaकरोw_मुक्त;
	काष्ठा blkfront_info *dev_info;
	काष्ठा blk_shaकरोw shaकरोw[];
पूर्ण;

/*
 * We have one of these per vbd, whether ide, scsi or 'other'.  They
 * hang in निजी_data off the gendisk काष्ठाure. We may end up
 * putting all kinds of पूर्णांकeresting stuff here :-)
 */
काष्ठा blkfront_info
अणु
	काष्ठा mutex mutex;
	काष्ठा xenbus_device *xbdev;
	काष्ठा gendisk *gd;
	u16 sector_size;
	अचिन्हित पूर्णांक physical_sector_size;
	पूर्णांक vdevice;
	blkअगर_vdev_t handle;
	क्रमागत blkअगर_state connected;
	/* Number of pages per ring buffer. */
	अचिन्हित पूर्णांक nr_ring_pages;
	काष्ठा request_queue *rq;
	अचिन्हित पूर्णांक feature_flush:1;
	अचिन्हित पूर्णांक feature_fua:1;
	अचिन्हित पूर्णांक feature_discard:1;
	अचिन्हित पूर्णांक feature_secdiscard:1;
	अचिन्हित पूर्णांक feature_persistent:1;
	अचिन्हित पूर्णांक discard_granularity;
	अचिन्हित पूर्णांक discard_alignment;
	/* Number of 4KB segments handled */
	अचिन्हित पूर्णांक max_indirect_segments;
	पूर्णांक is_पढ़ोy;
	काष्ठा blk_mq_tag_set tag_set;
	काष्ठा blkfront_ring_info *rinfo;
	अचिन्हित पूर्णांक nr_rings;
	अचिन्हित पूर्णांक rinfo_size;
	/* Save uncomplete reqs and bios क्रम migration. */
	काष्ठा list_head requests;
	काष्ठा bio_list bio_list;
	काष्ठा list_head info_list;
पूर्ण;

अटल अचिन्हित पूर्णांक nr_minors;
अटल अचिन्हित दीर्घ *minors;
अटल DEFINE_SPINLOCK(minor_lock);

#घोषणा GRANT_INVALID_REF	0

#घोषणा PARTS_PER_DISK		16
#घोषणा PARTS_PER_EXT_DISK      256

#घोषणा BLKIF_MAJOR(dev) ((dev)>>8)
#घोषणा BLKIF_MINOR(dev) ((dev) & 0xff)

#घोषणा EXT_SHIFT 28
#घोषणा EXTENDED (1<<EXT_SHIFT)
#घोषणा VDEV_IS_EXTENDED(dev) ((dev)&(EXTENDED))
#घोषणा BLKIF_MINOR_EXT(dev) ((dev)&(~EXTENDED))
#घोषणा EMULATED_HD_DISK_MINOR_OFFSET (0)
#घोषणा EMULATED_HD_DISK_NAME_OFFSET (EMULATED_HD_DISK_MINOR_OFFSET / 256)
#घोषणा EMULATED_SD_DISK_MINOR_OFFSET (0)
#घोषणा EMULATED_SD_DISK_NAME_OFFSET (EMULATED_SD_DISK_MINOR_OFFSET / 256)

#घोषणा DEV_NAME	"xvd"	/* name in /dev */

/*
 * Grants are always the same size as a Xen page (i.e 4KB).
 * A physical segment is always the same size as a Linux page.
 * Number of grants per physical segment
 */
#घोषणा GRANTS_PER_PSEG	(PAGE_SIZE / XEN_PAGE_SIZE)

#घोषणा GRANTS_PER_INसूचीECT_FRAME \
	(XEN_PAGE_SIZE / माप(काष्ठा blkअगर_request_segment))

#घोषणा INसूचीECT_GREFS(_grants)		\
	DIV_ROUND_UP(_grants, GRANTS_PER_INसूचीECT_FRAME)

अटल पूर्णांक blkfront_setup_indirect(काष्ठा blkfront_ring_info *rinfo);
अटल व्योम blkfront_gather_backend_features(काष्ठा blkfront_info *info);
अटल पूर्णांक negotiate_mq(काष्ठा blkfront_info *info);

#घोषणा क्रम_each_rinfo(info, ptr, idx)				\
	क्रम ((ptr) = (info)->rinfo, (idx) = 0;			\
	     (idx) < (info)->nr_rings;				\
	     (idx)++, (ptr) = (व्योम *)(ptr) + (info)->rinfo_size)

अटल अंतरभूत काष्ठा blkfront_ring_info *
get_rinfo(स्थिर काष्ठा blkfront_info *info, अचिन्हित पूर्णांक i)
अणु
	BUG_ON(i >= info->nr_rings);
	वापस (व्योम *)info->rinfo + i * info->rinfo_size;
पूर्ण

अटल पूर्णांक get_id_from_मुक्तlist(काष्ठा blkfront_ring_info *rinfo)
अणु
	अचिन्हित दीर्घ मुक्त = rinfo->shaकरोw_मुक्त;

	BUG_ON(मुक्त >= BLK_RING_SIZE(rinfo->dev_info));
	rinfo->shaकरोw_मुक्त = rinfo->shaकरोw[मुक्त].req.u.rw.id;
	rinfo->shaकरोw[मुक्त].req.u.rw.id = 0x0fffffee; /* debug */
	वापस मुक्त;
पूर्ण

अटल पूर्णांक add_id_to_मुक्तlist(काष्ठा blkfront_ring_info *rinfo,
			      अचिन्हित दीर्घ id)
अणु
	अगर (rinfo->shaकरोw[id].req.u.rw.id != id)
		वापस -EINVAL;
	अगर (rinfo->shaकरोw[id].request == शून्य)
		वापस -EINVAL;
	rinfo->shaकरोw[id].req.u.rw.id  = rinfo->shaकरोw_मुक्त;
	rinfo->shaकरोw[id].request = शून्य;
	rinfo->shaकरोw_मुक्त = id;
	वापस 0;
पूर्ण

अटल पूर्णांक fill_grant_buffer(काष्ठा blkfront_ring_info *rinfo, पूर्णांक num)
अणु
	काष्ठा blkfront_info *info = rinfo->dev_info;
	काष्ठा page *granted_page;
	काष्ठा grant *gnt_list_entry, *n;
	पूर्णांक i = 0;

	जबतक (i < num) अणु
		gnt_list_entry = kzalloc(माप(काष्ठा grant), GFP_NOIO);
		अगर (!gnt_list_entry)
			जाओ out_of_memory;

		अगर (info->feature_persistent) अणु
			granted_page = alloc_page(GFP_NOIO);
			अगर (!granted_page) अणु
				kमुक्त(gnt_list_entry);
				जाओ out_of_memory;
			पूर्ण
			gnt_list_entry->page = granted_page;
		पूर्ण

		gnt_list_entry->gref = GRANT_INVALID_REF;
		list_add(&gnt_list_entry->node, &rinfo->grants);
		i++;
	पूर्ण

	वापस 0;

out_of_memory:
	list_क्रम_each_entry_safe(gnt_list_entry, n,
	                         &rinfo->grants, node) अणु
		list_del(&gnt_list_entry->node);
		अगर (info->feature_persistent)
			__मुक्त_page(gnt_list_entry->page);
		kमुक्त(gnt_list_entry);
		i--;
	पूर्ण
	BUG_ON(i != 0);
	वापस -ENOMEM;
पूर्ण

अटल काष्ठा grant *get_मुक्त_grant(काष्ठा blkfront_ring_info *rinfo)
अणु
	काष्ठा grant *gnt_list_entry;

	BUG_ON(list_empty(&rinfo->grants));
	gnt_list_entry = list_first_entry(&rinfo->grants, काष्ठा grant,
					  node);
	list_del(&gnt_list_entry->node);

	अगर (gnt_list_entry->gref != GRANT_INVALID_REF)
		rinfo->persistent_gnts_c--;

	वापस gnt_list_entry;
पूर्ण

अटल अंतरभूत व्योम grant_क्रमeign_access(स्थिर काष्ठा grant *gnt_list_entry,
					स्थिर काष्ठा blkfront_info *info)
अणु
	gnttab_page_grant_क्रमeign_access_ref_one(gnt_list_entry->gref,
						 info->xbdev->otherend_id,
						 gnt_list_entry->page,
						 0);
पूर्ण

अटल काष्ठा grant *get_grant(grant_ref_t *gref_head,
			       अचिन्हित दीर्घ gfn,
			       काष्ठा blkfront_ring_info *rinfo)
अणु
	काष्ठा grant *gnt_list_entry = get_मुक्त_grant(rinfo);
	काष्ठा blkfront_info *info = rinfo->dev_info;

	अगर (gnt_list_entry->gref != GRANT_INVALID_REF)
		वापस gnt_list_entry;

	/* Assign a gref to this page */
	gnt_list_entry->gref = gnttab_claim_grant_reference(gref_head);
	BUG_ON(gnt_list_entry->gref == -ENOSPC);
	अगर (info->feature_persistent)
		grant_क्रमeign_access(gnt_list_entry, info);
	अन्यथा अणु
		/* Grant access to the GFN passed by the caller */
		gnttab_grant_क्रमeign_access_ref(gnt_list_entry->gref,
						info->xbdev->otherend_id,
						gfn, 0);
	पूर्ण

	वापस gnt_list_entry;
पूर्ण

अटल काष्ठा grant *get_indirect_grant(grant_ref_t *gref_head,
					काष्ठा blkfront_ring_info *rinfo)
अणु
	काष्ठा grant *gnt_list_entry = get_मुक्त_grant(rinfo);
	काष्ठा blkfront_info *info = rinfo->dev_info;

	अगर (gnt_list_entry->gref != GRANT_INVALID_REF)
		वापस gnt_list_entry;

	/* Assign a gref to this page */
	gnt_list_entry->gref = gnttab_claim_grant_reference(gref_head);
	BUG_ON(gnt_list_entry->gref == -ENOSPC);
	अगर (!info->feature_persistent) अणु
		काष्ठा page *indirect_page;

		/* Fetch a pre-allocated page to use क्रम indirect grefs */
		BUG_ON(list_empty(&rinfo->indirect_pages));
		indirect_page = list_first_entry(&rinfo->indirect_pages,
						 काष्ठा page, lru);
		list_del(&indirect_page->lru);
		gnt_list_entry->page = indirect_page;
	पूर्ण
	grant_क्रमeign_access(gnt_list_entry, info);

	वापस gnt_list_entry;
पूर्ण

अटल स्थिर अक्षर *op_name(पूर्णांक op)
अणु
	अटल स्थिर अक्षर *स्थिर names[] = अणु
		[BLKIF_OP_READ] = "read",
		[BLKIF_OP_WRITE] = "write",
		[BLKIF_OP_WRITE_BARRIER] = "barrier",
		[BLKIF_OP_FLUSH_DISKCACHE] = "flush",
		[BLKIF_OP_DISCARD] = "discard" पूर्ण;

	अगर (op < 0 || op >= ARRAY_SIZE(names))
		वापस "unknown";

	अगर (!names[op])
		वापस "reserved";

	वापस names[op];
पूर्ण
अटल पूर्णांक xlbd_reserve_minors(अचिन्हित पूर्णांक minor, अचिन्हित पूर्णांक nr)
अणु
	अचिन्हित पूर्णांक end = minor + nr;
	पूर्णांक rc;

	अगर (end > nr_minors) अणु
		अचिन्हित दीर्घ *biपंचांगap, *old;

		biपंचांगap = kसुस्मृति(BITS_TO_LONGS(end), माप(*biपंचांगap),
				 GFP_KERNEL);
		अगर (biपंचांगap == शून्य)
			वापस -ENOMEM;

		spin_lock(&minor_lock);
		अगर (end > nr_minors) अणु
			old = minors;
			स_नकल(biपंचांगap, minors,
			       BITS_TO_LONGS(nr_minors) * माप(*biपंचांगap));
			minors = biपंचांगap;
			nr_minors = BITS_TO_LONGS(end) * BITS_PER_LONG;
		पूर्ण अन्यथा
			old = biपंचांगap;
		spin_unlock(&minor_lock);
		kमुक्त(old);
	पूर्ण

	spin_lock(&minor_lock);
	अगर (find_next_bit(minors, end, minor) >= end) अणु
		biपंचांगap_set(minors, minor, nr);
		rc = 0;
	पूर्ण अन्यथा
		rc = -EBUSY;
	spin_unlock(&minor_lock);

	वापस rc;
पूर्ण

अटल व्योम xlbd_release_minors(अचिन्हित पूर्णांक minor, अचिन्हित पूर्णांक nr)
अणु
	अचिन्हित पूर्णांक end = minor + nr;

	BUG_ON(end > nr_minors);
	spin_lock(&minor_lock);
	biपंचांगap_clear(minors,  minor, nr);
	spin_unlock(&minor_lock);
पूर्ण

अटल व्योम blkअगर_restart_queue_callback(व्योम *arg)
अणु
	काष्ठा blkfront_ring_info *rinfo = (काष्ठा blkfront_ring_info *)arg;
	schedule_work(&rinfo->work);
पूर्ण

अटल पूर्णांक blkअगर_getgeo(काष्ठा block_device *bd, काष्ठा hd_geometry *hg)
अणु
	/* We करोn't have real geometry info, but let's at least वापस
	   values consistent with the size of the device */
	sector_t nsect = get_capacity(bd->bd_disk);
	sector_t cylinders = nsect;

	hg->heads = 0xff;
	hg->sectors = 0x3f;
	sector_भाग(cylinders, hg->heads * hg->sectors);
	hg->cylinders = cylinders;
	अगर ((sector_t)(hg->cylinders + 1) * hg->heads * hg->sectors < nsect)
		hg->cylinders = 0xffff;
	वापस 0;
पूर्ण

अटल पूर्णांक blkअगर_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
		       अचिन्हित command, अचिन्हित दीर्घ argument)
अणु
	काष्ठा blkfront_info *info = bdev->bd_disk->निजी_data;
	पूर्णांक i;

	dev_dbg(&info->xbdev->dev, "command: 0x%x, argument: 0x%lx\n",
		command, (दीर्घ)argument);

	चयन (command) अणु
	हाल CDROMMULTISESSION:
		dev_dbg(&info->xbdev->dev, "FIXME: support multisession CDs later\n");
		क्रम (i = 0; i < माप(काष्ठा cdrom_multisession); i++)
			अगर (put_user(0, (अक्षर __user *)(argument + i)))
				वापस -EFAULT;
		वापस 0;

	हाल CDROM_GET_CAPABILITY: अणु
		काष्ठा gendisk *gd = info->gd;
		अगर (gd->flags & GENHD_FL_CD)
			वापस 0;
		वापस -EINVAL;
	पूर्ण

	शेष:
		/*prपूर्णांकk(KERN_ALERT "ioctl %08x not supported by Xen blkdev\n",
		  command);*/
		वापस -EINVAL; /* same वापस as native Linux */
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ blkअगर_ring_get_request(काष्ठा blkfront_ring_info *rinfo,
					    काष्ठा request *req,
					    काष्ठा blkअगर_request **ring_req)
अणु
	अचिन्हित दीर्घ id;

	*ring_req = RING_GET_REQUEST(&rinfo->ring, rinfo->ring.req_prod_pvt);
	rinfo->ring.req_prod_pvt++;

	id = get_id_from_मुक्तlist(rinfo);
	rinfo->shaकरोw[id].request = req;
	rinfo->shaकरोw[id].status = REQ_WAITING;
	rinfo->shaकरोw[id].associated_id = NO_ASSOCIATED_ID;

	(*ring_req)->u.rw.id = id;

	वापस id;
पूर्ण

अटल पूर्णांक blkअगर_queue_discard_req(काष्ठा request *req, काष्ठा blkfront_ring_info *rinfo)
अणु
	काष्ठा blkfront_info *info = rinfo->dev_info;
	काष्ठा blkअगर_request *ring_req;
	अचिन्हित दीर्घ id;

	/* Fill out a communications ring काष्ठाure. */
	id = blkअगर_ring_get_request(rinfo, req, &ring_req);

	ring_req->operation = BLKIF_OP_DISCARD;
	ring_req->u.discard.nr_sectors = blk_rq_sectors(req);
	ring_req->u.discard.id = id;
	ring_req->u.discard.sector_number = (blkअगर_sector_t)blk_rq_pos(req);
	अगर (req_op(req) == REQ_OP_SECURE_ERASE && info->feature_secdiscard)
		ring_req->u.discard.flag = BLKIF_DISCARD_SECURE;
	अन्यथा
		ring_req->u.discard.flag = 0;

	/* Keep a निजी copy so we can reissue requests when recovering. */
	rinfo->shaकरोw[id].req = *ring_req;

	वापस 0;
पूर्ण

काष्ठा setup_rw_req अणु
	अचिन्हित पूर्णांक grant_idx;
	काष्ठा blkअगर_request_segment *segments;
	काष्ठा blkfront_ring_info *rinfo;
	काष्ठा blkअगर_request *ring_req;
	grant_ref_t gref_head;
	अचिन्हित पूर्णांक id;
	/* Only used when persistent grant is used and it's a पढ़ो request */
	bool need_copy;
	अचिन्हित पूर्णांक bvec_off;
	अक्षर *bvec_data;

	bool require_extra_req;
	काष्ठा blkअगर_request *extra_ring_req;
पूर्ण;

अटल व्योम blkअगर_setup_rw_req_grant(अचिन्हित दीर्घ gfn, अचिन्हित पूर्णांक offset,
				     अचिन्हित पूर्णांक len, व्योम *data)
अणु
	काष्ठा setup_rw_req *setup = data;
	पूर्णांक n, ref;
	काष्ठा grant *gnt_list_entry;
	अचिन्हित पूर्णांक fsect, lsect;
	/* Convenient aliases */
	अचिन्हित पूर्णांक grant_idx = setup->grant_idx;
	काष्ठा blkअगर_request *ring_req = setup->ring_req;
	काष्ठा blkfront_ring_info *rinfo = setup->rinfo;
	/*
	 * We always use the shaकरोw of the first request to store the list
	 * of grant associated to the block I/O request. This made the
	 * completion more easy to handle even अगर the block I/O request is
	 * split.
	 */
	काष्ठा blk_shaकरोw *shaकरोw = &rinfo->shaकरोw[setup->id];

	अगर (unlikely(setup->require_extra_req &&
		     grant_idx >= BLKIF_MAX_SEGMENTS_PER_REQUEST)) अणु
		/*
		 * We are using the second request, setup grant_idx
		 * to be the index of the segment array.
		 */
		grant_idx -= BLKIF_MAX_SEGMENTS_PER_REQUEST;
		ring_req = setup->extra_ring_req;
	पूर्ण

	अगर ((ring_req->operation == BLKIF_OP_INसूचीECT) &&
	    (grant_idx % GRANTS_PER_INसूचीECT_FRAME == 0)) अणु
		अगर (setup->segments)
			kunmap_atomic(setup->segments);

		n = grant_idx / GRANTS_PER_INसूचीECT_FRAME;
		gnt_list_entry = get_indirect_grant(&setup->gref_head, rinfo);
		shaकरोw->indirect_grants[n] = gnt_list_entry;
		setup->segments = kmap_atomic(gnt_list_entry->page);
		ring_req->u.indirect.indirect_grefs[n] = gnt_list_entry->gref;
	पूर्ण

	gnt_list_entry = get_grant(&setup->gref_head, gfn, rinfo);
	ref = gnt_list_entry->gref;
	/*
	 * All the grants are stored in the shaकरोw of the first
	 * request. Thereक्रमe we have to use the global index.
	 */
	shaकरोw->grants_used[setup->grant_idx] = gnt_list_entry;

	अगर (setup->need_copy) अणु
		व्योम *shared_data;

		shared_data = kmap_atomic(gnt_list_entry->page);
		/*
		 * this करोes not wipe data stored outside the
		 * range sg->offset..sg->offset+sg->length.
		 * Thereक्रमe, blkback *could* see data from
		 * previous requests. This is OK as दीर्घ as
		 * persistent grants are shared with just one
		 * करोमुख्य. It may need refactoring अगर this
		 * changes
		 */
		स_नकल(shared_data + offset,
		       setup->bvec_data + setup->bvec_off,
		       len);

		kunmap_atomic(shared_data);
		setup->bvec_off += len;
	पूर्ण

	fsect = offset >> 9;
	lsect = fsect + (len >> 9) - 1;
	अगर (ring_req->operation != BLKIF_OP_INसूचीECT) अणु
		ring_req->u.rw.seg[grant_idx] =
			(काष्ठा blkअगर_request_segment) अणु
				.gref       = ref,
				.first_sect = fsect,
				.last_sect  = lsect पूर्ण;
	पूर्ण अन्यथा अणु
		setup->segments[grant_idx % GRANTS_PER_INसूचीECT_FRAME] =
			(काष्ठा blkअगर_request_segment) अणु
				.gref       = ref,
				.first_sect = fsect,
				.last_sect  = lsect पूर्ण;
	पूर्ण

	(setup->grant_idx)++;
पूर्ण

अटल व्योम blkअगर_setup_extra_req(काष्ठा blkअगर_request *first,
				  काष्ठा blkअगर_request *second)
अणु
	uपूर्णांक16_t nr_segments = first->u.rw.nr_segments;

	/*
	 * The second request is only present when the first request uses
	 * all its segments. It's always the continuity of the first one.
	 */
	first->u.rw.nr_segments = BLKIF_MAX_SEGMENTS_PER_REQUEST;

	second->u.rw.nr_segments = nr_segments - BLKIF_MAX_SEGMENTS_PER_REQUEST;
	second->u.rw.sector_number = first->u.rw.sector_number +
		(BLKIF_MAX_SEGMENTS_PER_REQUEST * XEN_PAGE_SIZE) / 512;

	second->u.rw.handle = first->u.rw.handle;
	second->operation = first->operation;
पूर्ण

अटल पूर्णांक blkअगर_queue_rw_req(काष्ठा request *req, काष्ठा blkfront_ring_info *rinfo)
अणु
	काष्ठा blkfront_info *info = rinfo->dev_info;
	काष्ठा blkअगर_request *ring_req, *extra_ring_req = शून्य;
	अचिन्हित दीर्घ id, extra_id = NO_ASSOCIATED_ID;
	bool require_extra_req = false;
	पूर्णांक i;
	काष्ठा setup_rw_req setup = अणु
		.grant_idx = 0,
		.segments = शून्य,
		.rinfo = rinfo,
		.need_copy = rq_data_dir(req) && info->feature_persistent,
	पूर्ण;

	/*
	 * Used to store अगर we are able to queue the request by just using
	 * existing persistent grants, or अगर we have to get new grants,
	 * as there are not sufficiently many मुक्त.
	 */
	bool new_persistent_gnts = false;
	काष्ठा scatterlist *sg;
	पूर्णांक num_sg, max_grefs, num_grant;

	max_grefs = req->nr_phys_segments * GRANTS_PER_PSEG;
	अगर (max_grefs > BLKIF_MAX_SEGMENTS_PER_REQUEST)
		/*
		 * If we are using indirect segments we need to account
		 * क्रम the indirect grefs used in the request.
		 */
		max_grefs += INसूचीECT_GREFS(max_grefs);

	/* Check अगर we have enough persistent grants to allocate a requests */
	अगर (rinfo->persistent_gnts_c < max_grefs) अणु
		new_persistent_gnts = true;

		अगर (gnttab_alloc_grant_references(
		    max_grefs - rinfo->persistent_gnts_c,
		    &setup.gref_head) < 0) अणु
			gnttab_request_मुक्त_callback(
				&rinfo->callback,
				blkअगर_restart_queue_callback,
				rinfo,
				max_grefs - rinfo->persistent_gnts_c);
			वापस 1;
		पूर्ण
	पूर्ण

	/* Fill out a communications ring काष्ठाure. */
	id = blkअगर_ring_get_request(rinfo, req, &ring_req);

	num_sg = blk_rq_map_sg(req->q, req, rinfo->shaकरोw[id].sg);
	num_grant = 0;
	/* Calculate the number of grant used */
	क्रम_each_sg(rinfo->shaकरोw[id].sg, sg, num_sg, i)
	       num_grant += gnttab_count_grant(sg->offset, sg->length);

	require_extra_req = info->max_indirect_segments == 0 &&
		num_grant > BLKIF_MAX_SEGMENTS_PER_REQUEST;
	BUG_ON(!HAS_EXTRA_REQ && require_extra_req);

	rinfo->shaकरोw[id].num_sg = num_sg;
	अगर (num_grant > BLKIF_MAX_SEGMENTS_PER_REQUEST &&
	    likely(!require_extra_req)) अणु
		/*
		 * The indirect operation can only be a BLKIF_OP_READ or
		 * BLKIF_OP_WRITE
		 */
		BUG_ON(req_op(req) == REQ_OP_FLUSH || req->cmd_flags & REQ_FUA);
		ring_req->operation = BLKIF_OP_INसूचीECT;
		ring_req->u.indirect.indirect_op = rq_data_dir(req) ?
			BLKIF_OP_WRITE : BLKIF_OP_READ;
		ring_req->u.indirect.sector_number = (blkअगर_sector_t)blk_rq_pos(req);
		ring_req->u.indirect.handle = info->handle;
		ring_req->u.indirect.nr_segments = num_grant;
	पूर्ण अन्यथा अणु
		ring_req->u.rw.sector_number = (blkअगर_sector_t)blk_rq_pos(req);
		ring_req->u.rw.handle = info->handle;
		ring_req->operation = rq_data_dir(req) ?
			BLKIF_OP_WRITE : BLKIF_OP_READ;
		अगर (req_op(req) == REQ_OP_FLUSH || req->cmd_flags & REQ_FUA) अणु
			/*
			 * Ideally we can करो an unordered flush-to-disk.
			 * In हाल the backend onlysupports barriers, use that.
			 * A barrier request a superset of FUA, so we can
			 * implement it the same way.  (It's also a FLUSH+FUA,
			 * since it is guaranteed ordered WRT previous ग_लिखोs.)
			 */
			अगर (info->feature_flush && info->feature_fua)
				ring_req->operation =
					BLKIF_OP_WRITE_BARRIER;
			अन्यथा अगर (info->feature_flush)
				ring_req->operation =
					BLKIF_OP_FLUSH_DISKCACHE;
			अन्यथा
				ring_req->operation = 0;
		पूर्ण
		ring_req->u.rw.nr_segments = num_grant;
		अगर (unlikely(require_extra_req)) अणु
			extra_id = blkअगर_ring_get_request(rinfo, req,
							  &extra_ring_req);
			/*
			 * Only the first request contains the scatter-gather
			 * list.
			 */
			rinfo->shaकरोw[extra_id].num_sg = 0;

			blkअगर_setup_extra_req(ring_req, extra_ring_req);

			/* Link the 2 requests together */
			rinfo->shaकरोw[extra_id].associated_id = id;
			rinfo->shaकरोw[id].associated_id = extra_id;
		पूर्ण
	पूर्ण

	setup.ring_req = ring_req;
	setup.id = id;

	setup.require_extra_req = require_extra_req;
	अगर (unlikely(require_extra_req))
		setup.extra_ring_req = extra_ring_req;

	क्रम_each_sg(rinfo->shaकरोw[id].sg, sg, num_sg, i) अणु
		BUG_ON(sg->offset + sg->length > PAGE_SIZE);

		अगर (setup.need_copy) अणु
			setup.bvec_off = sg->offset;
			setup.bvec_data = kmap_atomic(sg_page(sg));
		पूर्ण

		gnttab_क्रमeach_grant_in_range(sg_page(sg),
					      sg->offset,
					      sg->length,
					      blkअगर_setup_rw_req_grant,
					      &setup);

		अगर (setup.need_copy)
			kunmap_atomic(setup.bvec_data);
	पूर्ण
	अगर (setup.segments)
		kunmap_atomic(setup.segments);

	/* Keep a निजी copy so we can reissue requests when recovering. */
	rinfo->shaकरोw[id].req = *ring_req;
	अगर (unlikely(require_extra_req))
		rinfo->shaकरोw[extra_id].req = *extra_ring_req;

	अगर (new_persistent_gnts)
		gnttab_मुक्त_grant_references(setup.gref_head);

	वापस 0;
पूर्ण

/*
 * Generate a Xen blkfront IO request from a blk layer request.  Reads
 * and ग_लिखोs are handled as expected.
 *
 * @req: a request काष्ठा
 */
अटल पूर्णांक blkअगर_queue_request(काष्ठा request *req, काष्ठा blkfront_ring_info *rinfo)
अणु
	अगर (unlikely(rinfo->dev_info->connected != BLKIF_STATE_CONNECTED))
		वापस 1;

	अगर (unlikely(req_op(req) == REQ_OP_DISCARD ||
		     req_op(req) == REQ_OP_SECURE_ERASE))
		वापस blkअगर_queue_discard_req(req, rinfo);
	अन्यथा
		वापस blkअगर_queue_rw_req(req, rinfo);
पूर्ण

अटल अंतरभूत व्योम flush_requests(काष्ठा blkfront_ring_info *rinfo)
अणु
	पूर्णांक notअगरy;

	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&rinfo->ring, notअगरy);

	अगर (notअगरy)
		notअगरy_remote_via_irq(rinfo->irq);
पूर्ण

अटल अंतरभूत bool blkअगर_request_flush_invalid(काष्ठा request *req,
					       काष्ठा blkfront_info *info)
अणु
	वापस (blk_rq_is_passthrough(req) ||
		((req_op(req) == REQ_OP_FLUSH) &&
		 !info->feature_flush) ||
		((req->cmd_flags & REQ_FUA) &&
		 !info->feature_fua));
पूर्ण

अटल blk_status_t blkअगर_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
			  स्थिर काष्ठा blk_mq_queue_data *qd)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक qid = hctx->queue_num;
	काष्ठा blkfront_info *info = hctx->queue->queuedata;
	काष्ठा blkfront_ring_info *rinfo = शून्य;

	rinfo = get_rinfo(info, qid);
	blk_mq_start_request(qd->rq);
	spin_lock_irqsave(&rinfo->ring_lock, flags);
	अगर (RING_FULL(&rinfo->ring))
		जाओ out_busy;

	अगर (blkअगर_request_flush_invalid(qd->rq, rinfo->dev_info))
		जाओ out_err;

	अगर (blkअगर_queue_request(qd->rq, rinfo))
		जाओ out_busy;

	flush_requests(rinfo);
	spin_unlock_irqrestore(&rinfo->ring_lock, flags);
	वापस BLK_STS_OK;

out_err:
	spin_unlock_irqrestore(&rinfo->ring_lock, flags);
	वापस BLK_STS_IOERR;

out_busy:
	blk_mq_stop_hw_queue(hctx);
	spin_unlock_irqrestore(&rinfo->ring_lock, flags);
	वापस BLK_STS_DEV_RESOURCE;
पूर्ण

अटल व्योम blkअगर_complete_rq(काष्ठा request *rq)
अणु
	blk_mq_end_request(rq, blkअगर_req(rq)->error);
पूर्ण

अटल स्थिर काष्ठा blk_mq_ops blkfront_mq_ops = अणु
	.queue_rq = blkअगर_queue_rq,
	.complete = blkअगर_complete_rq,
पूर्ण;

अटल व्योम blkअगर_set_queue_limits(काष्ठा blkfront_info *info)
अणु
	काष्ठा request_queue *rq = info->rq;
	काष्ठा gendisk *gd = info->gd;
	अचिन्हित पूर्णांक segments = info->max_indirect_segments ? :
				BLKIF_MAX_SEGMENTS_PER_REQUEST;

	blk_queue_flag_set(QUEUE_FLAG_VIRT, rq);

	अगर (info->feature_discard) अणु
		blk_queue_flag_set(QUEUE_FLAG_DISCARD, rq);
		blk_queue_max_discard_sectors(rq, get_capacity(gd));
		rq->limits.discard_granularity = info->discard_granularity ?:
						 info->physical_sector_size;
		rq->limits.discard_alignment = info->discard_alignment;
		अगर (info->feature_secdiscard)
			blk_queue_flag_set(QUEUE_FLAG_SECERASE, rq);
	पूर्ण

	/* Hard sector size and max sectors impersonate the equiv. hardware. */
	blk_queue_logical_block_size(rq, info->sector_size);
	blk_queue_physical_block_size(rq, info->physical_sector_size);
	blk_queue_max_hw_sectors(rq, (segments * XEN_PAGE_SIZE) / 512);

	/* Each segment in a request is up to an aligned page in size. */
	blk_queue_segment_boundary(rq, PAGE_SIZE - 1);
	blk_queue_max_segment_size(rq, PAGE_SIZE);

	/* Ensure a merged request will fit in a single I/O ring slot. */
	blk_queue_max_segments(rq, segments / GRANTS_PER_PSEG);

	/* Make sure buffer addresses are sector-aligned. */
	blk_queue_dma_alignment(rq, 511);
पूर्ण

अटल पूर्णांक xlvbd_init_blk_queue(काष्ठा gendisk *gd, u16 sector_size,
				अचिन्हित पूर्णांक physical_sector_size)
अणु
	काष्ठा request_queue *rq;
	काष्ठा blkfront_info *info = gd->निजी_data;

	स_रखो(&info->tag_set, 0, माप(info->tag_set));
	info->tag_set.ops = &blkfront_mq_ops;
	info->tag_set.nr_hw_queues = info->nr_rings;
	अगर (HAS_EXTRA_REQ && info->max_indirect_segments == 0) अणु
		/*
		 * When indirect descriptior is not supported, the I/O request
		 * will be split between multiple request in the ring.
		 * To aव्योम problems when sending the request, भागide by
		 * 2 the depth of the queue.
		 */
		info->tag_set.queue_depth =  BLK_RING_SIZE(info) / 2;
	पूर्ण अन्यथा
		info->tag_set.queue_depth = BLK_RING_SIZE(info);
	info->tag_set.numa_node = NUMA_NO_NODE;
	info->tag_set.flags = BLK_MQ_F_SHOULD_MERGE;
	info->tag_set.cmd_size = माप(काष्ठा blkअगर_req);
	info->tag_set.driver_data = info;

	अगर (blk_mq_alloc_tag_set(&info->tag_set))
		वापस -EINVAL;
	rq = blk_mq_init_queue(&info->tag_set);
	अगर (IS_ERR(rq)) अणु
		blk_mq_मुक्त_tag_set(&info->tag_set);
		वापस PTR_ERR(rq);
	पूर्ण

	rq->queuedata = info;
	info->rq = gd->queue = rq;
	info->gd = gd;
	info->sector_size = sector_size;
	info->physical_sector_size = physical_sector_size;
	blkअगर_set_queue_limits(info);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *flush_info(काष्ठा blkfront_info *info)
अणु
	अगर (info->feature_flush && info->feature_fua)
		वापस "barrier: enabled;";
	अन्यथा अगर (info->feature_flush)
		वापस "flush diskcache: enabled;";
	अन्यथा
		वापस "barrier or flush: disabled;";
पूर्ण

अटल व्योम xlvbd_flush(काष्ठा blkfront_info *info)
अणु
	blk_queue_ग_लिखो_cache(info->rq, info->feature_flush ? true : false,
			      info->feature_fua ? true : false);
	pr_info("blkfront: %s: %s %s %s %s %s\n",
		info->gd->disk_name, flush_info(info),
		"persistent grants:", info->feature_persistent ?
		"enabled;" : "disabled;", "indirect descriptors:",
		info->max_indirect_segments ? "enabled;" : "disabled;");
पूर्ण

अटल पूर्णांक xen_translate_vdev(पूर्णांक vdevice, पूर्णांक *minor, अचिन्हित पूर्णांक *offset)
अणु
	पूर्णांक major;
	major = BLKIF_MAJOR(vdevice);
	*minor = BLKIF_MINOR(vdevice);
	चयन (major) अणु
		हाल XEN_IDE0_MAJOR:
			*offset = (*minor / 64) + EMULATED_HD_DISK_NAME_OFFSET;
			*minor = ((*minor / 64) * PARTS_PER_DISK) +
				EMULATED_HD_DISK_MINOR_OFFSET;
			अवरोध;
		हाल XEN_IDE1_MAJOR:
			*offset = (*minor / 64) + 2 + EMULATED_HD_DISK_NAME_OFFSET;
			*minor = (((*minor / 64) + 2) * PARTS_PER_DISK) +
				EMULATED_HD_DISK_MINOR_OFFSET;
			अवरोध;
		हाल XEN_SCSI_DISK0_MAJOR:
			*offset = (*minor / PARTS_PER_DISK) + EMULATED_SD_DISK_NAME_OFFSET;
			*minor = *minor + EMULATED_SD_DISK_MINOR_OFFSET;
			अवरोध;
		हाल XEN_SCSI_DISK1_MAJOR:
		हाल XEN_SCSI_DISK2_MAJOR:
		हाल XEN_SCSI_DISK3_MAJOR:
		हाल XEN_SCSI_DISK4_MAJOR:
		हाल XEN_SCSI_DISK5_MAJOR:
		हाल XEN_SCSI_DISK6_MAJOR:
		हाल XEN_SCSI_DISK7_MAJOR:
			*offset = (*minor / PARTS_PER_DISK) + 
				((major - XEN_SCSI_DISK1_MAJOR + 1) * 16) +
				EMULATED_SD_DISK_NAME_OFFSET;
			*minor = *minor +
				((major - XEN_SCSI_DISK1_MAJOR + 1) * 16 * PARTS_PER_DISK) +
				EMULATED_SD_DISK_MINOR_OFFSET;
			अवरोध;
		हाल XEN_SCSI_DISK8_MAJOR:
		हाल XEN_SCSI_DISK9_MAJOR:
		हाल XEN_SCSI_DISK10_MAJOR:
		हाल XEN_SCSI_DISK11_MAJOR:
		हाल XEN_SCSI_DISK12_MAJOR:
		हाल XEN_SCSI_DISK13_MAJOR:
		हाल XEN_SCSI_DISK14_MAJOR:
		हाल XEN_SCSI_DISK15_MAJOR:
			*offset = (*minor / PARTS_PER_DISK) + 
				((major - XEN_SCSI_DISK8_MAJOR + 8) * 16) +
				EMULATED_SD_DISK_NAME_OFFSET;
			*minor = *minor +
				((major - XEN_SCSI_DISK8_MAJOR + 8) * 16 * PARTS_PER_DISK) +
				EMULATED_SD_DISK_MINOR_OFFSET;
			अवरोध;
		हाल XENVBD_MAJOR:
			*offset = *minor / PARTS_PER_DISK;
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_WARNING "blkfront: your disk configuration is "
					"incorrect, please use an xvd device instead\n");
			वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल अक्षर *encode_disk_name(अक्षर *ptr, अचिन्हित पूर्णांक n)
अणु
	अगर (n >= 26)
		ptr = encode_disk_name(ptr, n / 26 - 1);
	*ptr = 'a' + n % 26;
	वापस ptr + 1;
पूर्ण

अटल पूर्णांक xlvbd_alloc_gendisk(blkअगर_sector_t capacity,
			       काष्ठा blkfront_info *info,
			       u16 vdisk_info, u16 sector_size,
			       अचिन्हित पूर्णांक physical_sector_size)
अणु
	काष्ठा gendisk *gd;
	पूर्णांक nr_minors = 1;
	पूर्णांक err;
	अचिन्हित पूर्णांक offset;
	पूर्णांक minor;
	पूर्णांक nr_parts;
	अक्षर *ptr;

	BUG_ON(info->gd != शून्य);
	BUG_ON(info->rq != शून्य);

	अगर ((info->vdevice>>EXT_SHIFT) > 1) अणु
		/* this is above the extended range; something is wrong */
		prपूर्णांकk(KERN_WARNING "blkfront: vdevice 0x%x is above the extended range; ignoring\n", info->vdevice);
		वापस -ENODEV;
	पूर्ण

	अगर (!VDEV_IS_EXTENDED(info->vdevice)) अणु
		err = xen_translate_vdev(info->vdevice, &minor, &offset);
		अगर (err)
			वापस err;
		nr_parts = PARTS_PER_DISK;
	पूर्ण अन्यथा अणु
		minor = BLKIF_MINOR_EXT(info->vdevice);
		nr_parts = PARTS_PER_EXT_DISK;
		offset = minor / nr_parts;
		अगर (xen_hvm_करोमुख्य() && offset < EMULATED_HD_DISK_NAME_OFFSET + 4)
			prपूर्णांकk(KERN_WARNING "blkfront: vdevice 0x%x might conflict with "
					"emulated IDE disks,\n\t choose an xvd device name"
					"from xvde on\n", info->vdevice);
	पूर्ण
	अगर (minor >> MINORBITS) अणु
		pr_warn("blkfront: %#x's minor (%#x) out of range; ignoring\n",
			info->vdevice, minor);
		वापस -ENODEV;
	पूर्ण

	अगर ((minor % nr_parts) == 0)
		nr_minors = nr_parts;

	err = xlbd_reserve_minors(minor, nr_minors);
	अगर (err)
		जाओ out;
	err = -ENODEV;

	gd = alloc_disk(nr_minors);
	अगर (gd == शून्य)
		जाओ release;

	म_नकल(gd->disk_name, DEV_NAME);
	ptr = encode_disk_name(gd->disk_name + माप(DEV_NAME) - 1, offset);
	BUG_ON(ptr >= gd->disk_name + DISK_NAME_LEN);
	अगर (nr_minors > 1)
		*ptr = 0;
	अन्यथा
		snम_लिखो(ptr, gd->disk_name + DISK_NAME_LEN - ptr,
			 "%d", minor & (nr_parts - 1));

	gd->major = XENVBD_MAJOR;
	gd->first_minor = minor;
	gd->fops = &xlvbd_block_fops;
	gd->निजी_data = info;
	set_capacity(gd, capacity);

	अगर (xlvbd_init_blk_queue(gd, sector_size, physical_sector_size)) अणु
		del_gendisk(gd);
		जाओ release;
	पूर्ण

	xlvbd_flush(info);

	अगर (vdisk_info & VDISK_READONLY)
		set_disk_ro(gd, 1);

	अगर (vdisk_info & VDISK_REMOVABLE)
		gd->flags |= GENHD_FL_REMOVABLE;

	अगर (vdisk_info & VDISK_CDROM)
		gd->flags |= GENHD_FL_CD;

	वापस 0;

 release:
	xlbd_release_minors(minor, nr_minors);
 out:
	वापस err;
पूर्ण

अटल व्योम xlvbd_release_gendisk(काष्ठा blkfront_info *info)
अणु
	अचिन्हित पूर्णांक minor, nr_minors, i;
	काष्ठा blkfront_ring_info *rinfo;

	अगर (info->rq == शून्य)
		वापस;

	/* No more blkअगर_request(). */
	blk_mq_stop_hw_queues(info->rq);

	क्रम_each_rinfo(info, rinfo, i) अणु
		/* No more gnttab callback work. */
		gnttab_cancel_मुक्त_callback(&rinfo->callback);

		/* Flush gnttab callback work. Must be करोne with no locks held. */
		flush_work(&rinfo->work);
	पूर्ण

	del_gendisk(info->gd);

	minor = info->gd->first_minor;
	nr_minors = info->gd->minors;
	xlbd_release_minors(minor, nr_minors);

	blk_cleanup_queue(info->rq);
	blk_mq_मुक्त_tag_set(&info->tag_set);
	info->rq = शून्य;

	put_disk(info->gd);
	info->gd = शून्य;
पूर्ण

/* Alपढ़ोy hold rinfo->ring_lock. */
अटल अंतरभूत व्योम kick_pending_request_queues_locked(काष्ठा blkfront_ring_info *rinfo)
अणु
	अगर (!RING_FULL(&rinfo->ring))
		blk_mq_start_stopped_hw_queues(rinfo->dev_info->rq, true);
पूर्ण

अटल व्योम kick_pending_request_queues(काष्ठा blkfront_ring_info *rinfo)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rinfo->ring_lock, flags);
	kick_pending_request_queues_locked(rinfo);
	spin_unlock_irqrestore(&rinfo->ring_lock, flags);
पूर्ण

अटल व्योम blkअगर_restart_queue(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा blkfront_ring_info *rinfo = container_of(work, काष्ठा blkfront_ring_info, work);

	अगर (rinfo->dev_info->connected == BLKIF_STATE_CONNECTED)
		kick_pending_request_queues(rinfo);
पूर्ण

अटल व्योम blkअगर_मुक्त_ring(काष्ठा blkfront_ring_info *rinfo)
अणु
	काष्ठा grant *persistent_gnt, *n;
	काष्ठा blkfront_info *info = rinfo->dev_info;
	पूर्णांक i, j, segs;

	/*
	 * Remove indirect pages, this only happens when using indirect
	 * descriptors but not persistent grants
	 */
	अगर (!list_empty(&rinfo->indirect_pages)) अणु
		काष्ठा page *indirect_page, *n;

		BUG_ON(info->feature_persistent);
		list_क्रम_each_entry_safe(indirect_page, n, &rinfo->indirect_pages, lru) अणु
			list_del(&indirect_page->lru);
			__मुक्त_page(indirect_page);
		पूर्ण
	पूर्ण

	/* Remove all persistent grants. */
	अगर (!list_empty(&rinfo->grants)) अणु
		list_क्रम_each_entry_safe(persistent_gnt, n,
					 &rinfo->grants, node) अणु
			list_del(&persistent_gnt->node);
			अगर (persistent_gnt->gref != GRANT_INVALID_REF) अणु
				gnttab_end_क्रमeign_access(persistent_gnt->gref,
							  0, 0UL);
				rinfo->persistent_gnts_c--;
			पूर्ण
			अगर (info->feature_persistent)
				__मुक्त_page(persistent_gnt->page);
			kमुक्त(persistent_gnt);
		पूर्ण
	पूर्ण
	BUG_ON(rinfo->persistent_gnts_c != 0);

	क्रम (i = 0; i < BLK_RING_SIZE(info); i++) अणु
		/*
		 * Clear persistent grants present in requests alपढ़ोy
		 * on the shared ring
		 */
		अगर (!rinfo->shaकरोw[i].request)
			जाओ मुक्त_shaकरोw;

		segs = rinfo->shaकरोw[i].req.operation == BLKIF_OP_INसूचीECT ?
		       rinfo->shaकरोw[i].req.u.indirect.nr_segments :
		       rinfo->shaकरोw[i].req.u.rw.nr_segments;
		क्रम (j = 0; j < segs; j++) अणु
			persistent_gnt = rinfo->shaकरोw[i].grants_used[j];
			gnttab_end_क्रमeign_access(persistent_gnt->gref, 0, 0UL);
			अगर (info->feature_persistent)
				__मुक्त_page(persistent_gnt->page);
			kमुक्त(persistent_gnt);
		पूर्ण

		अगर (rinfo->shaकरोw[i].req.operation != BLKIF_OP_INसूचीECT)
			/*
			 * If this is not an indirect operation करोn't try to
			 * मुक्त indirect segments
			 */
			जाओ मुक्त_shaकरोw;

		क्रम (j = 0; j < INसूचीECT_GREFS(segs); j++) अणु
			persistent_gnt = rinfo->shaकरोw[i].indirect_grants[j];
			gnttab_end_क्रमeign_access(persistent_gnt->gref, 0, 0UL);
			__मुक्त_page(persistent_gnt->page);
			kमुक्त(persistent_gnt);
		पूर्ण

मुक्त_shaकरोw:
		kvमुक्त(rinfo->shaकरोw[i].grants_used);
		rinfo->shaकरोw[i].grants_used = शून्य;
		kvमुक्त(rinfo->shaकरोw[i].indirect_grants);
		rinfo->shaकरोw[i].indirect_grants = शून्य;
		kvमुक्त(rinfo->shaकरोw[i].sg);
		rinfo->shaकरोw[i].sg = शून्य;
	पूर्ण

	/* No more gnttab callback work. */
	gnttab_cancel_मुक्त_callback(&rinfo->callback);

	/* Flush gnttab callback work. Must be करोne with no locks held. */
	flush_work(&rinfo->work);

	/* Free resources associated with old device channel. */
	क्रम (i = 0; i < info->nr_ring_pages; i++) अणु
		अगर (rinfo->ring_ref[i] != GRANT_INVALID_REF) अणु
			gnttab_end_क्रमeign_access(rinfo->ring_ref[i], 0, 0);
			rinfo->ring_ref[i] = GRANT_INVALID_REF;
		पूर्ण
	पूर्ण
	मुक्त_pages((अचिन्हित दीर्घ)rinfo->ring.sring, get_order(info->nr_ring_pages * XEN_PAGE_SIZE));
	rinfo->ring.sring = शून्य;

	अगर (rinfo->irq)
		unbind_from_irqhandler(rinfo->irq, rinfo);
	rinfo->evtchn = rinfo->irq = 0;
पूर्ण

अटल व्योम blkअगर_मुक्त(काष्ठा blkfront_info *info, पूर्णांक suspend)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा blkfront_ring_info *rinfo;

	/* Prevent new requests being issued until we fix things up. */
	info->connected = suspend ?
		BLKIF_STATE_SUSPENDED : BLKIF_STATE_DISCONNECTED;
	/* No more blkअगर_request(). */
	अगर (info->rq)
		blk_mq_stop_hw_queues(info->rq);

	क्रम_each_rinfo(info, rinfo, i)
		blkअगर_मुक्त_ring(rinfo);

	kvमुक्त(info->rinfo);
	info->rinfo = शून्य;
	info->nr_rings = 0;
पूर्ण

काष्ठा copy_from_grant अणु
	स्थिर काष्ठा blk_shaकरोw *s;
	अचिन्हित पूर्णांक grant_idx;
	अचिन्हित पूर्णांक bvec_offset;
	अक्षर *bvec_data;
पूर्ण;

अटल व्योम blkअगर_copy_from_grant(अचिन्हित दीर्घ gfn, अचिन्हित पूर्णांक offset,
				  अचिन्हित पूर्णांक len, व्योम *data)
अणु
	काष्ठा copy_from_grant *info = data;
	अक्षर *shared_data;
	/* Convenient aliases */
	स्थिर काष्ठा blk_shaकरोw *s = info->s;

	shared_data = kmap_atomic(s->grants_used[info->grant_idx]->page);

	स_नकल(info->bvec_data + info->bvec_offset,
	       shared_data + offset, len);

	info->bvec_offset += len;
	info->grant_idx++;

	kunmap_atomic(shared_data);
पूर्ण

अटल क्रमागत blk_req_status blkअगर_rsp_to_req_status(पूर्णांक rsp)
अणु
	चयन (rsp)
	अणु
	हाल BLKIF_RSP_OKAY:
		वापस REQ_DONE;
	हाल BLKIF_RSP_EOPNOTSUPP:
		वापस REQ_EOPNOTSUPP;
	हाल BLKIF_RSP_ERROR:
	शेष:
		वापस REQ_ERROR;
	पूर्ण
पूर्ण

/*
 * Get the final status of the block request based on two ring response
 */
अटल पूर्णांक blkअगर_get_final_status(क्रमागत blk_req_status s1,
				  क्रमागत blk_req_status s2)
अणु
	BUG_ON(s1 == REQ_WAITING);
	BUG_ON(s2 == REQ_WAITING);

	अगर (s1 == REQ_ERROR || s2 == REQ_ERROR)
		वापस BLKIF_RSP_ERROR;
	अन्यथा अगर (s1 == REQ_EOPNOTSUPP || s2 == REQ_EOPNOTSUPP)
		वापस BLKIF_RSP_EOPNOTSUPP;
	वापस BLKIF_RSP_OKAY;
पूर्ण

अटल bool blkअगर_completion(अचिन्हित दीर्घ *id,
			     काष्ठा blkfront_ring_info *rinfo,
			     काष्ठा blkअगर_response *bret)
अणु
	पूर्णांक i = 0;
	काष्ठा scatterlist *sg;
	पूर्णांक num_sg, num_grant;
	काष्ठा blkfront_info *info = rinfo->dev_info;
	काष्ठा blk_shaकरोw *s = &rinfo->shaकरोw[*id];
	काष्ठा copy_from_grant data = अणु
		.grant_idx = 0,
	पूर्ण;

	num_grant = s->req.operation == BLKIF_OP_INसूचीECT ?
		s->req.u.indirect.nr_segments : s->req.u.rw.nr_segments;

	/* The I/O request may be split in two. */
	अगर (unlikely(s->associated_id != NO_ASSOCIATED_ID)) अणु
		काष्ठा blk_shaकरोw *s2 = &rinfo->shaकरोw[s->associated_id];

		/* Keep the status of the current response in shaकरोw. */
		s->status = blkअगर_rsp_to_req_status(bret->status);

		/* Wait the second response अगर not yet here. */
		अगर (s2->status == REQ_WAITING)
			वापस false;

		bret->status = blkअगर_get_final_status(s->status,
						      s2->status);

		/*
		 * All the grants is stored in the first shaकरोw in order
		 * to make the completion code simpler.
		 */
		num_grant += s2->req.u.rw.nr_segments;

		/*
		 * The two responses may not come in order. Only the
		 * first request will store the scatter-gather list.
		 */
		अगर (s2->num_sg != 0) अणु
			/* Update "id" with the ID of the first response. */
			*id = s->associated_id;
			s = s2;
		पूर्ण

		/*
		 * We करोn't need anymore the second request, so recycling
		 * it now.
		 */
		अगर (add_id_to_मुक्तlist(rinfo, s->associated_id))
			WARN(1, "%s: can't recycle the second part (id = %ld) of the request\n",
			     info->gd->disk_name, s->associated_id);
	पूर्ण

	data.s = s;
	num_sg = s->num_sg;

	अगर (bret->operation == BLKIF_OP_READ && info->feature_persistent) अणु
		क्रम_each_sg(s->sg, sg, num_sg, i) अणु
			BUG_ON(sg->offset + sg->length > PAGE_SIZE);

			data.bvec_offset = sg->offset;
			data.bvec_data = kmap_atomic(sg_page(sg));

			gnttab_क्रमeach_grant_in_range(sg_page(sg),
						      sg->offset,
						      sg->length,
						      blkअगर_copy_from_grant,
						      &data);

			kunmap_atomic(data.bvec_data);
		पूर्ण
	पूर्ण
	/* Add the persistent grant पूर्णांकo the list of मुक्त grants */
	क्रम (i = 0; i < num_grant; i++) अणु
		अगर (gnttab_query_क्रमeign_access(s->grants_used[i]->gref)) अणु
			/*
			 * If the grant is still mapped by the backend (the
			 * backend has chosen to make this grant persistent)
			 * we add it at the head of the list, so it will be
			 * reused first.
			 */
			अगर (!info->feature_persistent)
				pr_alert_ratelimited("backed has not unmapped grant: %u\n",
						     s->grants_used[i]->gref);
			list_add(&s->grants_used[i]->node, &rinfo->grants);
			rinfo->persistent_gnts_c++;
		पूर्ण अन्यथा अणु
			/*
			 * If the grant is not mapped by the backend we end the
			 * क्रमeign access and add it to the tail of the list,
			 * so it will not be picked again unless we run out of
			 * persistent grants.
			 */
			gnttab_end_क्रमeign_access(s->grants_used[i]->gref, 0, 0UL);
			s->grants_used[i]->gref = GRANT_INVALID_REF;
			list_add_tail(&s->grants_used[i]->node, &rinfo->grants);
		पूर्ण
	पूर्ण
	अगर (s->req.operation == BLKIF_OP_INसूचीECT) अणु
		क्रम (i = 0; i < INसूचीECT_GREFS(num_grant); i++) अणु
			अगर (gnttab_query_क्रमeign_access(s->indirect_grants[i]->gref)) अणु
				अगर (!info->feature_persistent)
					pr_alert_ratelimited("backed has not unmapped grant: %u\n",
							     s->indirect_grants[i]->gref);
				list_add(&s->indirect_grants[i]->node, &rinfo->grants);
				rinfo->persistent_gnts_c++;
			पूर्ण अन्यथा अणु
				काष्ठा page *indirect_page;

				gnttab_end_क्रमeign_access(s->indirect_grants[i]->gref, 0, 0UL);
				/*
				 * Add the used indirect page back to the list of
				 * available pages क्रम indirect grefs.
				 */
				अगर (!info->feature_persistent) अणु
					indirect_page = s->indirect_grants[i]->page;
					list_add(&indirect_page->lru, &rinfo->indirect_pages);
				पूर्ण
				s->indirect_grants[i]->gref = GRANT_INVALID_REF;
				list_add_tail(&s->indirect_grants[i]->node, &rinfo->grants);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल irqवापस_t blkअगर_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा request *req;
	काष्ठा blkअगर_response *bret;
	RING_IDX i, rp;
	अचिन्हित दीर्घ flags;
	काष्ठा blkfront_ring_info *rinfo = (काष्ठा blkfront_ring_info *)dev_id;
	काष्ठा blkfront_info *info = rinfo->dev_info;

	अगर (unlikely(info->connected != BLKIF_STATE_CONNECTED))
		वापस IRQ_HANDLED;

	spin_lock_irqsave(&rinfo->ring_lock, flags);
 again:
	rp = rinfo->ring.sring->rsp_prod;
	rmb(); /* Ensure we see queued responses up to 'rp'. */

	क्रम (i = rinfo->ring.rsp_cons; i != rp; i++) अणु
		अचिन्हित दीर्घ id;

		bret = RING_GET_RESPONSE(&rinfo->ring, i);
		id   = bret->id;
		/*
		 * The backend has messed up and given us an id that we would
		 * never have given to it (we stamp it up to BLK_RING_SIZE -
		 * look in get_id_from_मुक्तlist.
		 */
		अगर (id >= BLK_RING_SIZE(info)) अणु
			WARN(1, "%s: response to %s has incorrect id (%ld)\n",
			     info->gd->disk_name, op_name(bret->operation), id);
			/* We can't safely get the 'struct request' as
			 * the id is busted. */
			जारी;
		पूर्ण
		req  = rinfo->shaकरोw[id].request;

		अगर (bret->operation != BLKIF_OP_DISCARD) अणु
			/*
			 * We may need to रुको क्रम an extra response अगर the
			 * I/O request is split in 2
			 */
			अगर (!blkअगर_completion(&id, rinfo, bret))
				जारी;
		पूर्ण

		अगर (add_id_to_मुक्तlist(rinfo, id)) अणु
			WARN(1, "%s: response to %s (id %ld) couldn't be recycled!\n",
			     info->gd->disk_name, op_name(bret->operation), id);
			जारी;
		पूर्ण

		अगर (bret->status == BLKIF_RSP_OKAY)
			blkअगर_req(req)->error = BLK_STS_OK;
		अन्यथा
			blkअगर_req(req)->error = BLK_STS_IOERR;

		चयन (bret->operation) अणु
		हाल BLKIF_OP_DISCARD:
			अगर (unlikely(bret->status == BLKIF_RSP_EOPNOTSUPP)) अणु
				काष्ठा request_queue *rq = info->rq;
				prपूर्णांकk(KERN_WARNING "blkfront: %s: %s op failed\n",
					   info->gd->disk_name, op_name(bret->operation));
				blkअगर_req(req)->error = BLK_STS_NOTSUPP;
				info->feature_discard = 0;
				info->feature_secdiscard = 0;
				blk_queue_flag_clear(QUEUE_FLAG_DISCARD, rq);
				blk_queue_flag_clear(QUEUE_FLAG_SECERASE, rq);
			पूर्ण
			अवरोध;
		हाल BLKIF_OP_FLUSH_DISKCACHE:
		हाल BLKIF_OP_WRITE_BARRIER:
			अगर (unlikely(bret->status == BLKIF_RSP_EOPNOTSUPP)) अणु
				prपूर्णांकk(KERN_WARNING "blkfront: %s: %s op failed\n",
				       info->gd->disk_name, op_name(bret->operation));
				blkअगर_req(req)->error = BLK_STS_NOTSUPP;
			पूर्ण
			अगर (unlikely(bret->status == BLKIF_RSP_ERROR &&
				     rinfo->shaकरोw[id].req.u.rw.nr_segments == 0)) अणु
				prपूर्णांकk(KERN_WARNING "blkfront: %s: empty %s op failed\n",
				       info->gd->disk_name, op_name(bret->operation));
				blkअगर_req(req)->error = BLK_STS_NOTSUPP;
			पूर्ण
			अगर (unlikely(blkअगर_req(req)->error)) अणु
				अगर (blkअगर_req(req)->error == BLK_STS_NOTSUPP)
					blkअगर_req(req)->error = BLK_STS_OK;
				info->feature_fua = 0;
				info->feature_flush = 0;
				xlvbd_flush(info);
			पूर्ण
			fallthrough;
		हाल BLKIF_OP_READ:
		हाल BLKIF_OP_WRITE:
			अगर (unlikely(bret->status != BLKIF_RSP_OKAY))
				dev_dbg(&info->xbdev->dev, "Bad return from blkdev data "
					"request: %x\n", bret->status);

			अवरोध;
		शेष:
			BUG();
		पूर्ण

		अगर (likely(!blk_should_fake_समयout(req->q)))
			blk_mq_complete_request(req);
	पूर्ण

	rinfo->ring.rsp_cons = i;

	अगर (i != rinfo->ring.req_prod_pvt) अणु
		पूर्णांक more_to_करो;
		RING_FINAL_CHECK_FOR_RESPONSES(&rinfo->ring, more_to_करो);
		अगर (more_to_करो)
			जाओ again;
	पूर्ण अन्यथा
		rinfo->ring.sring->rsp_event = i + 1;

	kick_pending_request_queues_locked(rinfo);

	spin_unlock_irqrestore(&rinfo->ring_lock, flags);

	वापस IRQ_HANDLED;
पूर्ण


अटल पूर्णांक setup_blkring(काष्ठा xenbus_device *dev,
			 काष्ठा blkfront_ring_info *rinfo)
अणु
	काष्ठा blkअगर_sring *sring;
	पूर्णांक err, i;
	काष्ठा blkfront_info *info = rinfo->dev_info;
	अचिन्हित दीर्घ ring_size = info->nr_ring_pages * XEN_PAGE_SIZE;
	grant_ref_t gref[XENBUS_MAX_RING_GRANTS];

	क्रम (i = 0; i < info->nr_ring_pages; i++)
		rinfo->ring_ref[i] = GRANT_INVALID_REF;

	sring = (काष्ठा blkअगर_sring *)__get_मुक्त_pages(GFP_NOIO | __GFP_HIGH,
						       get_order(ring_size));
	अगर (!sring) अणु
		xenbus_dev_fatal(dev, -ENOMEM, "allocating shared ring");
		वापस -ENOMEM;
	पूर्ण
	SHARED_RING_INIT(sring);
	FRONT_RING_INIT(&rinfo->ring, sring, ring_size);

	err = xenbus_grant_ring(dev, rinfo->ring.sring, info->nr_ring_pages, gref);
	अगर (err < 0) अणु
		मुक्त_pages((अचिन्हित दीर्घ)sring, get_order(ring_size));
		rinfo->ring.sring = शून्य;
		जाओ fail;
	पूर्ण
	क्रम (i = 0; i < info->nr_ring_pages; i++)
		rinfo->ring_ref[i] = gref[i];

	err = xenbus_alloc_evtchn(dev, &rinfo->evtchn);
	अगर (err)
		जाओ fail;

	err = bind_evtchn_to_irqhandler(rinfo->evtchn, blkअगर_पूर्णांकerrupt, 0,
					"blkif", rinfo);
	अगर (err <= 0) अणु
		xenbus_dev_fatal(dev, err,
				 "bind_evtchn_to_irqhandler failed");
		जाओ fail;
	पूर्ण
	rinfo->irq = err;

	वापस 0;
fail:
	blkअगर_मुक्त(info, 0);
	वापस err;
पूर्ण

/*
 * Write out per-ring/queue nodes including ring-ref and event-channel, and each
 * ring buffer may have multi pages depending on ->nr_ring_pages.
 */
अटल पूर्णांक ग_लिखो_per_ring_nodes(काष्ठा xenbus_transaction xbt,
				काष्ठा blkfront_ring_info *rinfo, स्थिर अक्षर *dir)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक i;
	स्थिर अक्षर *message = शून्य;
	काष्ठा blkfront_info *info = rinfo->dev_info;

	अगर (info->nr_ring_pages == 1) अणु
		err = xenbus_म_लिखो(xbt, dir, "ring-ref", "%u", rinfo->ring_ref[0]);
		अगर (err) अणु
			message = "writing ring-ref";
			जाओ पात_transaction;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < info->nr_ring_pages; i++) अणु
			अक्षर ring_ref_name[RINGREF_NAME_LEN];

			snम_लिखो(ring_ref_name, RINGREF_NAME_LEN, "ring-ref%u", i);
			err = xenbus_म_लिखो(xbt, dir, ring_ref_name,
					    "%u", rinfo->ring_ref[i]);
			अगर (err) अणु
				message = "writing ring-ref";
				जाओ पात_transaction;
			पूर्ण
		पूर्ण
	पूर्ण

	err = xenbus_म_लिखो(xbt, dir, "event-channel", "%u", rinfo->evtchn);
	अगर (err) अणु
		message = "writing event-channel";
		जाओ पात_transaction;
	पूर्ण

	वापस 0;

पात_transaction:
	xenbus_transaction_end(xbt, 1);
	अगर (message)
		xenbus_dev_fatal(info->xbdev, err, "%s", message);

	वापस err;
पूर्ण

अटल व्योम मुक्त_info(काष्ठा blkfront_info *info)
अणु
	list_del(&info->info_list);
	kमुक्त(info);
पूर्ण

/* Common code used when first setting up, and when resuming. */
अटल पूर्णांक talk_to_blkback(काष्ठा xenbus_device *dev,
			   काष्ठा blkfront_info *info)
अणु
	स्थिर अक्षर *message = शून्य;
	काष्ठा xenbus_transaction xbt;
	पूर्णांक err;
	अचिन्हित पूर्णांक i, max_page_order;
	अचिन्हित पूर्णांक ring_page_order;
	काष्ठा blkfront_ring_info *rinfo;

	अगर (!info)
		वापस -ENODEV;

	max_page_order = xenbus_पढ़ो_अचिन्हित(info->xbdev->otherend,
					      "max-ring-page-order", 0);
	ring_page_order = min(xen_blkअगर_max_ring_order, max_page_order);
	info->nr_ring_pages = 1 << ring_page_order;

	err = negotiate_mq(info);
	अगर (err)
		जाओ destroy_blkring;

	क्रम_each_rinfo(info, rinfo, i) अणु
		/* Create shared ring, alloc event channel. */
		err = setup_blkring(dev, rinfo);
		अगर (err)
			जाओ destroy_blkring;
	पूर्ण

again:
	err = xenbus_transaction_start(&xbt);
	अगर (err) अणु
		xenbus_dev_fatal(dev, err, "starting transaction");
		जाओ destroy_blkring;
	पूर्ण

	अगर (info->nr_ring_pages > 1) अणु
		err = xenbus_म_लिखो(xbt, dev->nodename, "ring-page-order", "%u",
				    ring_page_order);
		अगर (err) अणु
			message = "writing ring-page-order";
			जाओ पात_transaction;
		पूर्ण
	पूर्ण

	/* We alपढ़ोy got the number of queues/rings in _probe */
	अगर (info->nr_rings == 1) अणु
		err = ग_लिखो_per_ring_nodes(xbt, info->rinfo, dev->nodename);
		अगर (err)
			जाओ destroy_blkring;
	पूर्ण अन्यथा अणु
		अक्षर *path;
		माप_प्रकार pathsize;

		err = xenbus_म_लिखो(xbt, dev->nodename, "multi-queue-num-queues", "%u",
				    info->nr_rings);
		अगर (err) अणु
			message = "writing multi-queue-num-queues";
			जाओ पात_transaction;
		पूर्ण

		pathsize = म_माप(dev->nodename) + QUEUE_NAME_LEN;
		path = kदो_स्मृति(pathsize, GFP_KERNEL);
		अगर (!path) अणु
			err = -ENOMEM;
			message = "ENOMEM while writing ring references";
			जाओ पात_transaction;
		पूर्ण

		क्रम_each_rinfo(info, rinfo, i) अणु
			स_रखो(path, 0, pathsize);
			snम_लिखो(path, pathsize, "%s/queue-%u", dev->nodename, i);
			err = ग_लिखो_per_ring_nodes(xbt, rinfo, path);
			अगर (err) अणु
				kमुक्त(path);
				जाओ destroy_blkring;
			पूर्ण
		पूर्ण
		kमुक्त(path);
	पूर्ण
	err = xenbus_म_लिखो(xbt, dev->nodename, "protocol", "%s",
			    XEN_IO_PROTO_ABI_NATIVE);
	अगर (err) अणु
		message = "writing protocol";
		जाओ पात_transaction;
	पूर्ण
	err = xenbus_म_लिखो(xbt, dev->nodename, "feature-persistent", "%u",
			info->feature_persistent);
	अगर (err)
		dev_warn(&dev->dev,
			 "writing persistent grants feature to xenbus");

	err = xenbus_transaction_end(xbt, 0);
	अगर (err) अणु
		अगर (err == -EAGAIN)
			जाओ again;
		xenbus_dev_fatal(dev, err, "completing transaction");
		जाओ destroy_blkring;
	पूर्ण

	क्रम_each_rinfo(info, rinfo, i) अणु
		अचिन्हित पूर्णांक j;

		क्रम (j = 0; j < BLK_RING_SIZE(info); j++)
			rinfo->shaकरोw[j].req.u.rw.id = j + 1;
		rinfo->shaकरोw[BLK_RING_SIZE(info)-1].req.u.rw.id = 0x0fffffff;
	पूर्ण
	xenbus_चयन_state(dev, XenbusStateInitialised);

	वापस 0;

 पात_transaction:
	xenbus_transaction_end(xbt, 1);
	अगर (message)
		xenbus_dev_fatal(dev, err, "%s", message);
 destroy_blkring:
	blkअगर_मुक्त(info, 0);

	mutex_lock(&blkfront_mutex);
	मुक्त_info(info);
	mutex_unlock(&blkfront_mutex);

	dev_set_drvdata(&dev->dev, शून्य);

	वापस err;
पूर्ण

अटल पूर्णांक negotiate_mq(काष्ठा blkfront_info *info)
अणु
	अचिन्हित पूर्णांक backend_max_queues;
	अचिन्हित पूर्णांक i;
	काष्ठा blkfront_ring_info *rinfo;

	BUG_ON(info->nr_rings);

	/* Check अगर backend supports multiple queues. */
	backend_max_queues = xenbus_पढ़ो_अचिन्हित(info->xbdev->otherend,
						  "multi-queue-max-queues", 1);
	info->nr_rings = min(backend_max_queues, xen_blkअगर_max_queues);
	/* We need at least one ring. */
	अगर (!info->nr_rings)
		info->nr_rings = 1;

	info->rinfo_size = काष्ठा_size(info->rinfo, shaकरोw,
				       BLK_RING_SIZE(info));
	info->rinfo = kvसुस्मृति(info->nr_rings, info->rinfo_size, GFP_KERNEL);
	अगर (!info->rinfo) अणु
		xenbus_dev_fatal(info->xbdev, -ENOMEM, "allocating ring_info structure");
		info->nr_rings = 0;
		वापस -ENOMEM;
	पूर्ण

	क्रम_each_rinfo(info, rinfo, i) अणु
		INIT_LIST_HEAD(&rinfo->indirect_pages);
		INIT_LIST_HEAD(&rinfo->grants);
		rinfo->dev_info = info;
		INIT_WORK(&rinfo->work, blkअगर_restart_queue);
		spin_lock_init(&rinfo->ring_lock);
	पूर्ण
	वापस 0;
पूर्ण

/* Enable the persistent grants feature. */
अटल bool feature_persistent = true;
module_param(feature_persistent, bool, 0644);
MODULE_PARM_DESC(feature_persistent,
		"Enables the persistent grants feature");

/*
 * Entry poपूर्णांक to this code when a new device is created.  Allocate the basic
 * काष्ठाures and the ring buffer क्रम communication with the backend, and
 * inक्रमm the backend of the appropriate details क्रम those.  Switch to
 * Initialised state.
 */
अटल पूर्णांक blkfront_probe(काष्ठा xenbus_device *dev,
			  स्थिर काष्ठा xenbus_device_id *id)
अणु
	पूर्णांक err, vdevice;
	काष्ठा blkfront_info *info;

	/* FIXME: Use dynamic device id अगर this is not set. */
	err = xenbus_म_पूछो(XBT_NIL, dev->nodename,
			   "virtual-device", "%i", &vdevice);
	अगर (err != 1) अणु
		/* go looking in the extended area instead */
		err = xenbus_म_पूछो(XBT_NIL, dev->nodename, "virtual-device-ext",
				   "%i", &vdevice);
		अगर (err != 1) अणु
			xenbus_dev_fatal(dev, err, "reading virtual-device");
			वापस err;
		पूर्ण
	पूर्ण

	अगर (xen_hvm_करोमुख्य()) अणु
		अक्षर *type;
		पूर्णांक len;
		/* no unplug has been करोne: करो not hook devices != xen vbds */
		अगर (xen_has_pv_and_legacy_disk_devices()) अणु
			पूर्णांक major;

			अगर (!VDEV_IS_EXTENDED(vdevice))
				major = BLKIF_MAJOR(vdevice);
			अन्यथा
				major = XENVBD_MAJOR;

			अगर (major != XENVBD_MAJOR) अणु
				prपूर्णांकk(KERN_INFO
						"%s: HVM does not support vbd %d as xen block device\n",
						__func__, vdevice);
				वापस -ENODEV;
			पूर्ण
		पूर्ण
		/* करो not create a PV cdrom device अगर we are an HVM guest */
		type = xenbus_पढ़ो(XBT_NIL, dev->nodename, "device-type", &len);
		अगर (IS_ERR(type))
			वापस -ENODEV;
		अगर (म_भेदन(type, "cdrom", 5) == 0) अणु
			kमुक्त(type);
			वापस -ENODEV;
		पूर्ण
		kमुक्त(type);
	पूर्ण
	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info) अणु
		xenbus_dev_fatal(dev, -ENOMEM, "allocating info structure");
		वापस -ENOMEM;
	पूर्ण

	info->xbdev = dev;

	mutex_init(&info->mutex);
	info->vdevice = vdevice;
	info->connected = BLKIF_STATE_DISCONNECTED;

	info->feature_persistent = feature_persistent;

	/* Front end dir is a number, which is used as the id. */
	info->handle = simple_म_से_अदीर्घ(म_खोजप(dev->nodename, '/')+1, शून्य, 0);
	dev_set_drvdata(&dev->dev, info);

	mutex_lock(&blkfront_mutex);
	list_add(&info->info_list, &info_list);
	mutex_unlock(&blkfront_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक blkअगर_recover(काष्ठा blkfront_info *info)
अणु
	अचिन्हित पूर्णांक r_index;
	काष्ठा request *req, *n;
	पूर्णांक rc;
	काष्ठा bio *bio;
	अचिन्हित पूर्णांक segs;
	काष्ठा blkfront_ring_info *rinfo;

	blkfront_gather_backend_features(info);
	/* Reset limits changed by blk_mq_update_nr_hw_queues(). */
	blkअगर_set_queue_limits(info);
	segs = info->max_indirect_segments ? : BLKIF_MAX_SEGMENTS_PER_REQUEST;
	blk_queue_max_segments(info->rq, segs / GRANTS_PER_PSEG);

	क्रम_each_rinfo(info, rinfo, r_index) अणु
		rc = blkfront_setup_indirect(rinfo);
		अगर (rc)
			वापस rc;
	पूर्ण
	xenbus_चयन_state(info->xbdev, XenbusStateConnected);

	/* Now safe क्रम us to use the shared ring */
	info->connected = BLKIF_STATE_CONNECTED;

	क्रम_each_rinfo(info, rinfo, r_index) अणु
		/* Kick any other new requests queued since we resumed */
		kick_pending_request_queues(rinfo);
	पूर्ण

	list_क्रम_each_entry_safe(req, n, &info->requests, queuelist) अणु
		/* Requeue pending requests (flush or discard) */
		list_del_init(&req->queuelist);
		BUG_ON(req->nr_phys_segments > segs);
		blk_mq_requeue_request(req, false);
	पूर्ण
	blk_mq_start_stopped_hw_queues(info->rq, true);
	blk_mq_kick_requeue_list(info->rq);

	जबतक ((bio = bio_list_pop(&info->bio_list)) != शून्य) अणु
		/* Traverse the list of pending bios and re-queue them */
		submit_bio(bio);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * We are reconnecting to the backend, due to a suspend/resume, or a backend
 * driver restart.  We tear करोwn our blkअगर काष्ठाure and recreate it, but
 * leave the device-layer काष्ठाures पूर्णांकact so that this is transparent to the
 * rest of the kernel.
 */
अटल पूर्णांक blkfront_resume(काष्ठा xenbus_device *dev)
अणु
	काष्ठा blkfront_info *info = dev_get_drvdata(&dev->dev);
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक i, j;
	काष्ठा blkfront_ring_info *rinfo;

	dev_dbg(&dev->dev, "blkfront_resume: %s\n", dev->nodename);

	bio_list_init(&info->bio_list);
	INIT_LIST_HEAD(&info->requests);
	क्रम_each_rinfo(info, rinfo, i) अणु
		काष्ठा bio_list merge_bio;
		काष्ठा blk_shaकरोw *shaकरोw = rinfo->shaकरोw;

		क्रम (j = 0; j < BLK_RING_SIZE(info); j++) अणु
			/* Not in use? */
			अगर (!shaकरोw[j].request)
				जारी;

			/*
			 * Get the bios in the request so we can re-queue them.
			 */
			अगर (req_op(shaकरोw[j].request) == REQ_OP_FLUSH ||
			    req_op(shaकरोw[j].request) == REQ_OP_DISCARD ||
			    req_op(shaकरोw[j].request) == REQ_OP_SECURE_ERASE ||
			    shaकरोw[j].request->cmd_flags & REQ_FUA) अणु
				/*
				 * Flush operations करोn't contain bios, so
				 * we need to requeue the whole request
				 *
				 * XXX: but this करोesn't make any sense क्रम a
				 * ग_लिखो with the FUA flag set..
				 */
				list_add(&shaकरोw[j].request->queuelist, &info->requests);
				जारी;
			पूर्ण
			merge_bपन.सead = shaकरोw[j].request->bio;
			merge_bio.tail = shaकरोw[j].request->biotail;
			bio_list_merge(&info->bio_list, &merge_bio);
			shaकरोw[j].request->bio = शून्य;
			blk_mq_end_request(shaकरोw[j].request, BLK_STS_OK);
		पूर्ण
	पूर्ण

	blkअगर_मुक्त(info, info->connected == BLKIF_STATE_CONNECTED);

	err = talk_to_blkback(dev, info);
	अगर (!err)
		blk_mq_update_nr_hw_queues(&info->tag_set, info->nr_rings);

	/*
	 * We have to रुको क्रम the backend to चयन to
	 * connected state, since we want to पढ़ो which
	 * features it supports.
	 */

	वापस err;
पूर्ण

अटल व्योम blkfront_closing(काष्ठा blkfront_info *info)
अणु
	काष्ठा xenbus_device *xbdev = info->xbdev;
	काष्ठा block_device *bdev = शून्य;

	mutex_lock(&info->mutex);

	अगर (xbdev->state == XenbusStateClosing) अणु
		mutex_unlock(&info->mutex);
		वापस;
	पूर्ण

	अगर (info->gd)
		bdev = bdgrab(info->gd->part0);

	mutex_unlock(&info->mutex);

	अगर (!bdev) अणु
		xenbus_frontend_बंदd(xbdev);
		वापस;
	पूर्ण

	mutex_lock(&bdev->bd_mutex);

	अगर (bdev->bd_खोलोers) अणु
		xenbus_dev_error(xbdev, -EBUSY,
				 "Device in use; refusing to close");
		xenbus_चयन_state(xbdev, XenbusStateClosing);
	पूर्ण अन्यथा अणु
		xlvbd_release_gendisk(info);
		xenbus_frontend_बंदd(xbdev);
	पूर्ण

	mutex_unlock(&bdev->bd_mutex);
	bdput(bdev);
पूर्ण

अटल व्योम blkfront_setup_discard(काष्ठा blkfront_info *info)
अणु
	info->feature_discard = 1;
	info->discard_granularity = xenbus_पढ़ो_अचिन्हित(info->xbdev->otherend,
							 "discard-granularity",
							 0);
	info->discard_alignment = xenbus_पढ़ो_अचिन्हित(info->xbdev->otherend,
						       "discard-alignment", 0);
	info->feature_secdiscard =
		!!xenbus_पढ़ो_अचिन्हित(info->xbdev->otherend, "discard-secure",
				       0);
पूर्ण

अटल पूर्णांक blkfront_setup_indirect(काष्ठा blkfront_ring_info *rinfo)
अणु
	अचिन्हित पूर्णांक psegs, grants, memflags;
	पूर्णांक err, i;
	काष्ठा blkfront_info *info = rinfo->dev_info;

	memflags = meदो_स्मृति_noio_save();

	अगर (info->max_indirect_segments == 0) अणु
		अगर (!HAS_EXTRA_REQ)
			grants = BLKIF_MAX_SEGMENTS_PER_REQUEST;
		अन्यथा अणु
			/*
			 * When an extra req is required, the maximum
			 * grants supported is related to the size of the
			 * Linux block segment.
			 */
			grants = GRANTS_PER_PSEG;
		पूर्ण
	पूर्ण
	अन्यथा
		grants = info->max_indirect_segments;
	psegs = DIV_ROUND_UP(grants, GRANTS_PER_PSEG);

	err = fill_grant_buffer(rinfo,
				(grants + INसूचीECT_GREFS(grants)) * BLK_RING_SIZE(info));
	अगर (err)
		जाओ out_of_memory;

	अगर (!info->feature_persistent && info->max_indirect_segments) अणु
		/*
		 * We are using indirect descriptors but not persistent
		 * grants, we need to allocate a set of pages that can be
		 * used क्रम mapping indirect grefs
		 */
		पूर्णांक num = INसूचीECT_GREFS(grants) * BLK_RING_SIZE(info);

		BUG_ON(!list_empty(&rinfo->indirect_pages));
		क्रम (i = 0; i < num; i++) अणु
			काष्ठा page *indirect_page = alloc_page(GFP_KERNEL);
			अगर (!indirect_page)
				जाओ out_of_memory;
			list_add(&indirect_page->lru, &rinfo->indirect_pages);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < BLK_RING_SIZE(info); i++) अणु
		rinfo->shaकरोw[i].grants_used =
			kvसुस्मृति(grants,
				 माप(rinfo->shaकरोw[i].grants_used[0]),
				 GFP_KERNEL);
		rinfo->shaकरोw[i].sg = kvसुस्मृति(psegs,
					       माप(rinfo->shaकरोw[i].sg[0]),
					       GFP_KERNEL);
		अगर (info->max_indirect_segments)
			rinfo->shaकरोw[i].indirect_grants =
				kvसुस्मृति(INसूचीECT_GREFS(grants),
					 माप(rinfo->shaकरोw[i].indirect_grants[0]),
					 GFP_KERNEL);
		अगर ((rinfo->shaकरोw[i].grants_used == शून्य) ||
			(rinfo->shaकरोw[i].sg == शून्य) ||
		     (info->max_indirect_segments &&
		     (rinfo->shaकरोw[i].indirect_grants == शून्य)))
			जाओ out_of_memory;
		sg_init_table(rinfo->shaकरोw[i].sg, psegs);
	पूर्ण

	meदो_स्मृति_noio_restore(memflags);

	वापस 0;

out_of_memory:
	क्रम (i = 0; i < BLK_RING_SIZE(info); i++) अणु
		kvमुक्त(rinfo->shaकरोw[i].grants_used);
		rinfo->shaकरोw[i].grants_used = शून्य;
		kvमुक्त(rinfo->shaकरोw[i].sg);
		rinfo->shaकरोw[i].sg = शून्य;
		kvमुक्त(rinfo->shaकरोw[i].indirect_grants);
		rinfo->shaकरोw[i].indirect_grants = शून्य;
	पूर्ण
	अगर (!list_empty(&rinfo->indirect_pages)) अणु
		काष्ठा page *indirect_page, *n;
		list_क्रम_each_entry_safe(indirect_page, n, &rinfo->indirect_pages, lru) अणु
			list_del(&indirect_page->lru);
			__मुक्त_page(indirect_page);
		पूर्ण
	पूर्ण

	meदो_स्मृति_noio_restore(memflags);

	वापस -ENOMEM;
पूर्ण

/*
 * Gather all backend feature-*
 */
अटल व्योम blkfront_gather_backend_features(काष्ठा blkfront_info *info)
अणु
	अचिन्हित पूर्णांक indirect_segments;

	info->feature_flush = 0;
	info->feature_fua = 0;

	/*
	 * If there's no "feature-barrier" defined, then it means
	 * we're dealing with a very old backend which ग_लिखोs
	 * synchronously; nothing to करो.
	 *
	 * If there are barriers, then we use flush.
	 */
	अगर (xenbus_पढ़ो_अचिन्हित(info->xbdev->otherend, "feature-barrier", 0)) अणु
		info->feature_flush = 1;
		info->feature_fua = 1;
	पूर्ण

	/*
	 * And अगर there is "feature-flush-cache" use that above
	 * barriers.
	 */
	अगर (xenbus_पढ़ो_अचिन्हित(info->xbdev->otherend, "feature-flush-cache",
				 0)) अणु
		info->feature_flush = 1;
		info->feature_fua = 0;
	पूर्ण

	अगर (xenbus_पढ़ो_अचिन्हित(info->xbdev->otherend, "feature-discard", 0))
		blkfront_setup_discard(info);

	अगर (info->feature_persistent)
		info->feature_persistent =
			!!xenbus_पढ़ो_अचिन्हित(info->xbdev->otherend,
					       "feature-persistent", 0);

	indirect_segments = xenbus_पढ़ो_अचिन्हित(info->xbdev->otherend,
					"feature-max-indirect-segments", 0);
	अगर (indirect_segments > xen_blkअगर_max_segments)
		indirect_segments = xen_blkअगर_max_segments;
	अगर (indirect_segments <= BLKIF_MAX_SEGMENTS_PER_REQUEST)
		indirect_segments = 0;
	info->max_indirect_segments = indirect_segments;

	अगर (info->feature_persistent) अणु
		mutex_lock(&blkfront_mutex);
		schedule_delayed_work(&blkfront_work, HZ * 10);
		mutex_unlock(&blkfront_mutex);
	पूर्ण
पूर्ण

/*
 * Invoked when the backend is finally 'ready' (and has told produced
 * the details about the physical device - #sectors, size, etc).
 */
अटल व्योम blkfront_connect(काष्ठा blkfront_info *info)
अणु
	अचिन्हित दीर्घ दीर्घ sectors;
	अचिन्हित दीर्घ sector_size;
	अचिन्हित पूर्णांक physical_sector_size;
	अचिन्हित पूर्णांक binfo;
	पूर्णांक err, i;
	काष्ठा blkfront_ring_info *rinfo;

	चयन (info->connected) अणु
	हाल BLKIF_STATE_CONNECTED:
		/*
		 * Potentially, the back-end may be संकेतling
		 * a capacity change; update the capacity.
		 */
		err = xenbus_म_पूछो(XBT_NIL, info->xbdev->otherend,
				   "sectors", "%Lu", &sectors);
		अगर (XENBUS_EXIST_ERR(err))
			वापस;
		prपूर्णांकk(KERN_INFO "Setting capacity to %Lu\n",
		       sectors);
		set_capacity_and_notअगरy(info->gd, sectors);

		वापस;
	हाल BLKIF_STATE_SUSPENDED:
		/*
		 * If we are recovering from suspension, we need to रुको
		 * क्रम the backend to announce it's features beक्रमe
		 * reconnecting, at least we need to know अगर the backend
		 * supports indirect descriptors, and how many.
		 */
		blkअगर_recover(info);
		वापस;

	शेष:
		अवरोध;
	पूर्ण

	dev_dbg(&info->xbdev->dev, "%s:%s.\n",
		__func__, info->xbdev->otherend);

	err = xenbus_gather(XBT_NIL, info->xbdev->otherend,
			    "sectors", "%llu", &sectors,
			    "info", "%u", &binfo,
			    "sector-size", "%lu", &sector_size,
			    शून्य);
	अगर (err) अणु
		xenbus_dev_fatal(info->xbdev, err,
				 "reading backend fields at %s",
				 info->xbdev->otherend);
		वापस;
	पूर्ण

	/*
	 * physical-sector-size is a newer field, so old backends may not
	 * provide this. Assume physical sector size to be the same as
	 * sector_size in that हाल.
	 */
	physical_sector_size = xenbus_पढ़ो_अचिन्हित(info->xbdev->otherend,
						    "physical-sector-size",
						    sector_size);
	blkfront_gather_backend_features(info);
	क्रम_each_rinfo(info, rinfo, i) अणु
		err = blkfront_setup_indirect(rinfo);
		अगर (err) अणु
			xenbus_dev_fatal(info->xbdev, err, "setup_indirect at %s",
					 info->xbdev->otherend);
			blkअगर_मुक्त(info, 0);
			अवरोध;
		पूर्ण
	पूर्ण

	err = xlvbd_alloc_gendisk(sectors, info, binfo, sector_size,
				  physical_sector_size);
	अगर (err) अणु
		xenbus_dev_fatal(info->xbdev, err, "xlvbd_add at %s",
				 info->xbdev->otherend);
		जाओ fail;
	पूर्ण

	xenbus_चयन_state(info->xbdev, XenbusStateConnected);

	/* Kick pending requests. */
	info->connected = BLKIF_STATE_CONNECTED;
	क्रम_each_rinfo(info, rinfo, i)
		kick_pending_request_queues(rinfo);

	device_add_disk(&info->xbdev->dev, info->gd, शून्य);

	info->is_पढ़ोy = 1;
	वापस;

fail:
	blkअगर_मुक्त(info, 0);
	वापस;
पूर्ण

/*
 * Callback received when the backend's state changes.
 */
अटल व्योम blkback_changed(काष्ठा xenbus_device *dev,
			    क्रमागत xenbus_state backend_state)
अणु
	काष्ठा blkfront_info *info = dev_get_drvdata(&dev->dev);

	dev_dbg(&dev->dev, "blkfront:blkback_changed to state %d.\n", backend_state);

	चयन (backend_state) अणु
	हाल XenbusStateInitWait:
		अगर (dev->state != XenbusStateInitialising)
			अवरोध;
		अगर (talk_to_blkback(dev, info))
			अवरोध;
		अवरोध;
	हाल XenbusStateInitialising:
	हाल XenbusStateInitialised:
	हाल XenbusStateReconfiguring:
	हाल XenbusStateReconfigured:
	हाल XenbusStateUnknown:
		अवरोध;

	हाल XenbusStateConnected:
		/*
		 * talk_to_blkback sets state to XenbusStateInitialised
		 * and blkfront_connect sets it to XenbusStateConnected
		 * (अगर connection went OK).
		 *
		 * If the backend (or toolstack) decides to poke at backend
		 * state (and re-trigger the watch by setting the state repeatedly
		 * to XenbusStateConnected (4)) we need to deal with this.
		 * This is allowed as this is used to communicate to the guest
		 * that the size of disk has changed!
		 */
		अगर ((dev->state != XenbusStateInitialised) &&
		    (dev->state != XenbusStateConnected)) अणु
			अगर (talk_to_blkback(dev, info))
				अवरोध;
		पूर्ण

		blkfront_connect(info);
		अवरोध;

	हाल XenbusStateClosed:
		अगर (dev->state == XenbusStateClosed)
			अवरोध;
		fallthrough;
	हाल XenbusStateClosing:
		अगर (info)
			blkfront_closing(info);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक blkfront_हटाओ(काष्ठा xenbus_device *xbdev)
अणु
	काष्ठा blkfront_info *info = dev_get_drvdata(&xbdev->dev);
	काष्ठा block_device *bdev = शून्य;
	काष्ठा gendisk *disk;

	dev_dbg(&xbdev->dev, "%s removed", xbdev->nodename);

	अगर (!info)
		वापस 0;

	blkअगर_मुक्त(info, 0);

	mutex_lock(&info->mutex);

	disk = info->gd;
	अगर (disk)
		bdev = bdgrab(disk->part0);

	info->xbdev = शून्य;
	mutex_unlock(&info->mutex);

	अगर (!bdev) अणु
		mutex_lock(&blkfront_mutex);
		मुक्त_info(info);
		mutex_unlock(&blkfront_mutex);
		वापस 0;
	पूर्ण

	/*
	 * The xbdev was हटाओd beक्रमe we reached the Closed
	 * state. See अगर it's safe to हटाओ the disk. If the bdev
	 * isn't बंदd yet, we let release take care of it.
	 */

	mutex_lock(&bdev->bd_mutex);
	info = disk->निजी_data;

	dev_warn(disk_to_dev(disk),
		 "%s was hot-unplugged, %d stale handles\n",
		 xbdev->nodename, bdev->bd_खोलोers);

	अगर (info && !bdev->bd_खोलोers) अणु
		xlvbd_release_gendisk(info);
		disk->निजी_data = शून्य;
		mutex_lock(&blkfront_mutex);
		मुक्त_info(info);
		mutex_unlock(&blkfront_mutex);
	पूर्ण

	mutex_unlock(&bdev->bd_mutex);
	bdput(bdev);

	वापस 0;
पूर्ण

अटल पूर्णांक blkfront_is_पढ़ोy(काष्ठा xenbus_device *dev)
अणु
	काष्ठा blkfront_info *info = dev_get_drvdata(&dev->dev);

	वापस info->is_पढ़ोy && info->xbdev;
पूर्ण

अटल पूर्णांक blkअगर_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा gendisk *disk = bdev->bd_disk;
	काष्ठा blkfront_info *info;
	पूर्णांक err = 0;

	mutex_lock(&blkfront_mutex);

	info = disk->निजी_data;
	अगर (!info) अणु
		/* xbdev gone */
		err = -ERESTARTSYS;
		जाओ out;
	पूर्ण

	mutex_lock(&info->mutex);

	अगर (!info->gd)
		/* xbdev is बंदd */
		err = -ERESTARTSYS;

	mutex_unlock(&info->mutex);

out:
	mutex_unlock(&blkfront_mutex);
	वापस err;
पूर्ण

अटल व्योम blkअगर_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा blkfront_info *info = disk->निजी_data;
	काष्ठा xenbus_device *xbdev;

	mutex_lock(&blkfront_mutex);
	अगर (disk->part0->bd_खोलोers)
		जाओ out_mutex;

	/*
	 * Check अगर we have been inकाष्ठाed to बंद. We will have
	 * deferred this request, because the bdev was still खोलो.
	 */

	mutex_lock(&info->mutex);
	xbdev = info->xbdev;

	अगर (xbdev && xbdev->state == XenbusStateClosing) अणु
		/* pending चयन to state बंदd */
		dev_info(disk_to_dev(disk), "releasing disk\n");
		xlvbd_release_gendisk(info);
		xenbus_frontend_बंदd(info->xbdev);
 	पूर्ण

	mutex_unlock(&info->mutex);

	अगर (!xbdev) अणु
		/* sudden device removal */
		dev_info(disk_to_dev(disk), "releasing disk\n");
		xlvbd_release_gendisk(info);
		disk->निजी_data = शून्य;
		मुक्त_info(info);
	पूर्ण

out_mutex:
	mutex_unlock(&blkfront_mutex);
पूर्ण

अटल स्थिर काष्ठा block_device_operations xlvbd_block_fops =
अणु
	.owner = THIS_MODULE,
	.खोलो = blkअगर_खोलो,
	.release = blkअगर_release,
	.getgeo = blkअगर_getgeo,
	.ioctl = blkअगर_ioctl,
	.compat_ioctl = blkdev_compat_ptr_ioctl,
पूर्ण;


अटल स्थिर काष्ठा xenbus_device_id blkfront_ids[] = अणु
	अणु "vbd" पूर्ण,
	अणु "" पूर्ण
पूर्ण;

अटल काष्ठा xenbus_driver blkfront_driver = अणु
	.ids  = blkfront_ids,
	.probe = blkfront_probe,
	.हटाओ = blkfront_हटाओ,
	.resume = blkfront_resume,
	.otherend_changed = blkback_changed,
	.is_पढ़ोy = blkfront_is_पढ़ोy,
पूर्ण;

अटल व्योम purge_persistent_grants(काष्ठा blkfront_info *info)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;
	काष्ठा blkfront_ring_info *rinfo;

	क्रम_each_rinfo(info, rinfo, i) अणु
		काष्ठा grant *gnt_list_entry, *पंचांगp;

		spin_lock_irqsave(&rinfo->ring_lock, flags);

		अगर (rinfo->persistent_gnts_c == 0) अणु
			spin_unlock_irqrestore(&rinfo->ring_lock, flags);
			जारी;
		पूर्ण

		list_क्रम_each_entry_safe(gnt_list_entry, पंचांगp, &rinfo->grants,
					 node) अणु
			अगर (gnt_list_entry->gref == GRANT_INVALID_REF ||
			    gnttab_query_क्रमeign_access(gnt_list_entry->gref))
				जारी;

			list_del(&gnt_list_entry->node);
			gnttab_end_क्रमeign_access(gnt_list_entry->gref, 0, 0UL);
			rinfo->persistent_gnts_c--;
			gnt_list_entry->gref = GRANT_INVALID_REF;
			list_add_tail(&gnt_list_entry->node, &rinfo->grants);
		पूर्ण

		spin_unlock_irqrestore(&rinfo->ring_lock, flags);
	पूर्ण
पूर्ण

अटल व्योम blkfront_delay_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा blkfront_info *info;
	bool need_schedule_work = false;

	mutex_lock(&blkfront_mutex);

	list_क्रम_each_entry(info, &info_list, info_list) अणु
		अगर (info->feature_persistent) अणु
			need_schedule_work = true;
			mutex_lock(&info->mutex);
			purge_persistent_grants(info);
			mutex_unlock(&info->mutex);
		पूर्ण
	पूर्ण

	अगर (need_schedule_work)
		schedule_delayed_work(&blkfront_work, HZ * 10);

	mutex_unlock(&blkfront_mutex);
पूर्ण

अटल पूर्णांक __init xlblk_init(व्योम)
अणु
	पूर्णांक ret;
	पूर्णांक nr_cpus = num_online_cpus();

	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	अगर (!xen_has_pv_disk_devices())
		वापस -ENODEV;

	अगर (रेजिस्टर_blkdev(XENVBD_MAJOR, DEV_NAME)) अणु
		pr_warn("xen_blk: can't get major %d with name %s\n",
			XENVBD_MAJOR, DEV_NAME);
		वापस -ENODEV;
	पूर्ण

	अगर (xen_blkअगर_max_segments < BLKIF_MAX_SEGMENTS_PER_REQUEST)
		xen_blkअगर_max_segments = BLKIF_MAX_SEGMENTS_PER_REQUEST;

	अगर (xen_blkअगर_max_ring_order > XENBUS_MAX_RING_GRANT_ORDER) अणु
		pr_info("Invalid max_ring_order (%d), will use default max: %d.\n",
			xen_blkअगर_max_ring_order, XENBUS_MAX_RING_GRANT_ORDER);
		xen_blkअगर_max_ring_order = XENBUS_MAX_RING_GRANT_ORDER;
	पूर्ण

	अगर (xen_blkअगर_max_queues > nr_cpus) अणु
		pr_info("Invalid max_queues (%d), will use default max: %d.\n",
			xen_blkअगर_max_queues, nr_cpus);
		xen_blkअगर_max_queues = nr_cpus;
	पूर्ण

	INIT_DELAYED_WORK(&blkfront_work, blkfront_delay_work);

	ret = xenbus_रेजिस्टर_frontend(&blkfront_driver);
	अगर (ret) अणु
		unरेजिस्टर_blkdev(XENVBD_MAJOR, DEV_NAME);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
module_init(xlblk_init);


अटल व्योम __निकास xlblk_निकास(व्योम)
अणु
	cancel_delayed_work_sync(&blkfront_work);

	xenbus_unरेजिस्टर_driver(&blkfront_driver);
	unरेजिस्टर_blkdev(XENVBD_MAJOR, DEV_NAME);
	kमुक्त(minors);
पूर्ण
module_निकास(xlblk_निकास);

MODULE_DESCRIPTION("Xen virtual block device frontend");
MODULE_LICENSE("GPL");
MODULE_ALIAS_BLOCKDEV_MAJOR(XENVBD_MAJOR);
MODULE_ALIAS("xen:vbd");
MODULE_ALIAS("xenblk");
