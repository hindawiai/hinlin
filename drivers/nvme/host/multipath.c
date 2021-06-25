<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2017-2018 Christoph Hellwig.
 */

#समावेश <linux/backing-dev.h>
#समावेश <linux/moduleparam.h>
#समावेश <trace/events/block.h>
#समावेश "nvme.h"

अटल bool multipath = true;
module_param(multipath, bool, 0444);
MODULE_PARM_DESC(multipath,
	"turn on native support for multiple controllers per subsystem");

व्योम nvme_mpath_unमुक्तze(काष्ठा nvme_subप्रणाली *subsys)
अणु
	काष्ठा nvme_ns_head *h;

	lockdep_निश्चित_held(&subsys->lock);
	list_क्रम_each_entry(h, &subsys->nsheads, entry)
		अगर (h->disk)
			blk_mq_unमुक्तze_queue(h->disk->queue);
पूर्ण

व्योम nvme_mpath_रुको_मुक्तze(काष्ठा nvme_subप्रणाली *subsys)
अणु
	काष्ठा nvme_ns_head *h;

	lockdep_निश्चित_held(&subsys->lock);
	list_क्रम_each_entry(h, &subsys->nsheads, entry)
		अगर (h->disk)
			blk_mq_मुक्तze_queue_रुको(h->disk->queue);
पूर्ण

व्योम nvme_mpath_start_मुक्तze(काष्ठा nvme_subप्रणाली *subsys)
अणु
	काष्ठा nvme_ns_head *h;

	lockdep_निश्चित_held(&subsys->lock);
	list_क्रम_each_entry(h, &subsys->nsheads, entry)
		अगर (h->disk)
			blk_मुक्तze_queue_start(h->disk->queue);
पूर्ण

/*
 * If multipathing is enabled we need to always use the subप्रणाली instance
 * number क्रम numbering our devices to aव्योम conflicts between subप्रणालीs that
 * have multiple controllers and thus use the multipath-aware subप्रणाली node
 * and those that have a single controller and use the controller node
 * directly.
 */
bool nvme_mpath_set_disk_name(काष्ठा nvme_ns *ns, अक्षर *disk_name, पूर्णांक *flags)
अणु
	अगर (!multipath)
		वापस false;
	अगर (!ns->head->disk) अणु
		प्र_लिखो(disk_name, "nvme%dn%d", ns->ctrl->subsys->instance,
			ns->head->instance);
		वापस true;
	पूर्ण
	प्र_लिखो(disk_name, "nvme%dc%dn%d", ns->ctrl->subsys->instance,
		ns->ctrl->instance, ns->head->instance);
	*flags = GENHD_FL_HIDDEN;
	वापस true;
पूर्ण

व्योम nvme_failover_req(काष्ठा request *req)
अणु
	काष्ठा nvme_ns *ns = req->q->queuedata;
	u16 status = nvme_req(req)->status & 0x7ff;
	अचिन्हित दीर्घ flags;
	काष्ठा bio *bio;

	nvme_mpath_clear_current_path(ns);

	/*
	 * If we got back an ANA error, we know the controller is alive but not
	 * पढ़ोy to serve this namespace.  Kick of a re-पढ़ो of the ANA
	 * inक्रमmation page, and just try any other available path क्रम now.
	 */
	अगर (nvme_is_ana_error(status) && ns->ctrl->ana_log_buf) अणु
		set_bit(NVME_NS_ANA_PENDING, &ns->flags);
		queue_work(nvme_wq, &ns->ctrl->ana_work);
	पूर्ण

	spin_lock_irqsave(&ns->head->requeue_lock, flags);
	क्रम (bio = req->bio; bio; bio = bio->bi_next)
		bio_set_dev(bio, ns->head->disk->part0);
	blk_steal_bios(&ns->head->requeue_list, req);
	spin_unlock_irqrestore(&ns->head->requeue_lock, flags);

	blk_mq_end_request(req, 0);
	kblockd_schedule_work(&ns->head->requeue_work);
पूर्ण

व्योम nvme_kick_requeue_lists(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा nvme_ns *ns;

	करोwn_पढ़ो(&ctrl->namespaces_rwsem);
	list_क्रम_each_entry(ns, &ctrl->namespaces, list) अणु
		अगर (ns->head->disk)
			kblockd_schedule_work(&ns->head->requeue_work);
	पूर्ण
	up_पढ़ो(&ctrl->namespaces_rwsem);
पूर्ण

अटल स्थिर अक्षर *nvme_ana_state_names[] = अणु
	[0]				= "invalid state",
	[NVME_ANA_OPTIMIZED]		= "optimized",
	[NVME_ANA_NONOPTIMIZED]		= "non-optimized",
	[NVME_ANA_INACCESSIBLE]		= "inaccessible",
	[NVME_ANA_PERSISTENT_LOSS]	= "persistent-loss",
	[NVME_ANA_CHANGE]		= "change",
पूर्ण;

bool nvme_mpath_clear_current_path(काष्ठा nvme_ns *ns)
अणु
	काष्ठा nvme_ns_head *head = ns->head;
	bool changed = false;
	पूर्णांक node;

	अगर (!head)
		जाओ out;

	क्रम_each_node(node) अणु
		अगर (ns == rcu_access_poपूर्णांकer(head->current_path[node])) अणु
			rcu_assign_poपूर्णांकer(head->current_path[node], शून्य);
			changed = true;
		पूर्ण
	पूर्ण
out:
	वापस changed;
पूर्ण

व्योम nvme_mpath_clear_ctrl_paths(काष्ठा nvme_ctrl *ctrl)
अणु
	काष्ठा nvme_ns *ns;

	mutex_lock(&ctrl->scan_lock);
	करोwn_पढ़ो(&ctrl->namespaces_rwsem);
	list_क्रम_each_entry(ns, &ctrl->namespaces, list)
		अगर (nvme_mpath_clear_current_path(ns))
			kblockd_schedule_work(&ns->head->requeue_work);
	up_पढ़ो(&ctrl->namespaces_rwsem);
	mutex_unlock(&ctrl->scan_lock);
पूर्ण

अटल bool nvme_path_is_disabled(काष्ठा nvme_ns *ns)
अणु
	/*
	 * We करोn't treat NVME_CTRL_DELETING as a disabled path as I/O should
	 * still be able to complete assuming that the controller is connected.
	 * Otherwise it will fail immediately and वापस to the requeue list.
	 */
	अगर (ns->ctrl->state != NVME_CTRL_LIVE &&
	    ns->ctrl->state != NVME_CTRL_DELETING)
		वापस true;
	अगर (test_bit(NVME_NS_ANA_PENDING, &ns->flags) ||
	    test_bit(NVME_NS_REMOVING, &ns->flags))
		वापस true;
	वापस false;
पूर्ण

अटल काष्ठा nvme_ns *__nvme_find_path(काष्ठा nvme_ns_head *head, पूर्णांक node)
अणु
	पूर्णांक found_distance = पूर्णांक_उच्च, fallback_distance = पूर्णांक_उच्च, distance;
	काष्ठा nvme_ns *found = शून्य, *fallback = शून्य, *ns;

	list_क्रम_each_entry_rcu(ns, &head->list, siblings) अणु
		अगर (nvme_path_is_disabled(ns))
			जारी;

		अगर (READ_ONCE(head->subsys->iopolicy) == NVME_IOPOLICY_NUMA)
			distance = node_distance(node, ns->ctrl->numa_node);
		अन्यथा
			distance = LOCAL_DISTANCE;

		चयन (ns->ana_state) अणु
		हाल NVME_ANA_OPTIMIZED:
			अगर (distance < found_distance) अणु
				found_distance = distance;
				found = ns;
			पूर्ण
			अवरोध;
		हाल NVME_ANA_NONOPTIMIZED:
			अगर (distance < fallback_distance) अणु
				fallback_distance = distance;
				fallback = ns;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found)
		found = fallback;
	अगर (found)
		rcu_assign_poपूर्णांकer(head->current_path[node], found);
	वापस found;
पूर्ण

अटल काष्ठा nvme_ns *nvme_next_ns(काष्ठा nvme_ns_head *head,
		काष्ठा nvme_ns *ns)
अणु
	ns = list_next_or_null_rcu(&head->list, &ns->siblings, काष्ठा nvme_ns,
			siblings);
	अगर (ns)
		वापस ns;
	वापस list_first_or_null_rcu(&head->list, काष्ठा nvme_ns, siblings);
पूर्ण

अटल काष्ठा nvme_ns *nvme_round_robin_path(काष्ठा nvme_ns_head *head,
		पूर्णांक node, काष्ठा nvme_ns *old)
अणु
	काष्ठा nvme_ns *ns, *found = शून्य;

	अगर (list_is_singular(&head->list)) अणु
		अगर (nvme_path_is_disabled(old))
			वापस शून्य;
		वापस old;
	पूर्ण

	क्रम (ns = nvme_next_ns(head, old);
	     ns && ns != old;
	     ns = nvme_next_ns(head, ns)) अणु
		अगर (nvme_path_is_disabled(ns))
			जारी;

		अगर (ns->ana_state == NVME_ANA_OPTIMIZED) अणु
			found = ns;
			जाओ out;
		पूर्ण
		अगर (ns->ana_state == NVME_ANA_NONOPTIMIZED)
			found = ns;
	पूर्ण

	/*
	 * The loop above skips the current path क्रम round-robin semantics.
	 * Fall back to the current path अगर either:
	 *  - no other optimized path found and current is optimized,
	 *  - no other usable path found and current is usable.
	 */
	अगर (!nvme_path_is_disabled(old) &&
	    (old->ana_state == NVME_ANA_OPTIMIZED ||
	     (!found && old->ana_state == NVME_ANA_NONOPTIMIZED)))
		वापस old;

	अगर (!found)
		वापस शून्य;
out:
	rcu_assign_poपूर्णांकer(head->current_path[node], found);
	वापस found;
पूर्ण

अटल अंतरभूत bool nvme_path_is_optimized(काष्ठा nvme_ns *ns)
अणु
	वापस ns->ctrl->state == NVME_CTRL_LIVE &&
		ns->ana_state == NVME_ANA_OPTIMIZED;
पूर्ण

अंतरभूत काष्ठा nvme_ns *nvme_find_path(काष्ठा nvme_ns_head *head)
अणु
	पूर्णांक node = numa_node_id();
	काष्ठा nvme_ns *ns;

	ns = srcu_dereference(head->current_path[node], &head->srcu);
	अगर (unlikely(!ns))
		वापस __nvme_find_path(head, node);

	अगर (READ_ONCE(head->subsys->iopolicy) == NVME_IOPOLICY_RR)
		वापस nvme_round_robin_path(head, node, ns);
	अगर (unlikely(!nvme_path_is_optimized(ns)))
		वापस __nvme_find_path(head, node);
	वापस ns;
पूर्ण

अटल bool nvme_available_path(काष्ठा nvme_ns_head *head)
अणु
	काष्ठा nvme_ns *ns;

	list_क्रम_each_entry_rcu(ns, &head->list, siblings) अणु
		अगर (test_bit(NVME_CTRL_FAILFAST_EXPIRED, &ns->ctrl->flags))
			जारी;
		चयन (ns->ctrl->state) अणु
		हाल NVME_CTRL_LIVE:
		हाल NVME_CTRL_RESETTING:
		हाल NVME_CTRL_CONNECTING:
			/* fallthru */
			वापस true;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल blk_qc_t nvme_ns_head_submit_bio(काष्ठा bio *bio)
अणु
	काष्ठा nvme_ns_head *head = bio->bi_bdev->bd_disk->निजी_data;
	काष्ठा device *dev = disk_to_dev(head->disk);
	काष्ठा nvme_ns *ns;
	blk_qc_t ret = BLK_QC_T_NONE;
	पूर्णांक srcu_idx;

	/*
	 * The namespace might be going away and the bio might be moved to a
	 * dअगरferent queue via blk_steal_bios(), so we need to use the bio_split
	 * pool from the original queue to allocate the bvecs from.
	 */
	blk_queue_split(&bio);

	srcu_idx = srcu_पढ़ो_lock(&head->srcu);
	ns = nvme_find_path(head);
	अगर (likely(ns)) अणु
		bio_set_dev(bio, ns->disk->part0);
		bio->bi_opf |= REQ_NVME_MPATH;
		trace_block_bio_remap(bio, disk_devt(ns->head->disk),
				      bio->bi_iter.bi_sector);
		ret = submit_bio_noacct(bio);
	पूर्ण अन्यथा अगर (nvme_available_path(head)) अणु
		dev_warn_ratelimited(dev, "no usable path - requeuing I/O\n");

		spin_lock_irq(&head->requeue_lock);
		bio_list_add(&head->requeue_list, bio);
		spin_unlock_irq(&head->requeue_lock);
	पूर्ण अन्यथा अणु
		dev_warn_ratelimited(dev, "no available path - failing I/O\n");

		bio->bi_status = BLK_STS_IOERR;
		bio_endio(bio);
	पूर्ण

	srcu_पढ़ो_unlock(&head->srcu, srcu_idx);
	वापस ret;
पूर्ण

अटल पूर्णांक nvme_ns_head_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	अगर (!nvme_tryget_ns_head(bdev->bd_disk->निजी_data))
		वापस -ENXIO;
	वापस 0;
पूर्ण

अटल व्योम nvme_ns_head_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	nvme_put_ns_head(disk->निजी_data);
पूर्ण

स्थिर काष्ठा block_device_operations nvme_ns_head_ops = अणु
	.owner		= THIS_MODULE,
	.submit_bio	= nvme_ns_head_submit_bio,
	.खोलो		= nvme_ns_head_खोलो,
	.release	= nvme_ns_head_release,
	.ioctl		= nvme_ns_head_ioctl,
	.getgeo		= nvme_getgeo,
	.report_zones	= nvme_report_zones,
	.pr_ops		= &nvme_pr_ops,
पूर्ण;

अटल अंतरभूत काष्ठा nvme_ns_head *cdev_to_ns_head(काष्ठा cdev *cdev)
अणु
	वापस container_of(cdev, काष्ठा nvme_ns_head, cdev);
पूर्ण

अटल पूर्णांक nvme_ns_head_chr_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (!nvme_tryget_ns_head(cdev_to_ns_head(inode->i_cdev)))
		वापस -ENXIO;
	वापस 0;
पूर्ण

अटल पूर्णांक nvme_ns_head_chr_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	nvme_put_ns_head(cdev_to_ns_head(inode->i_cdev));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations nvme_ns_head_chr_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= nvme_ns_head_chr_खोलो,
	.release	= nvme_ns_head_chr_release,
	.unlocked_ioctl	= nvme_ns_head_chr_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
पूर्ण;

अटल पूर्णांक nvme_add_ns_head_cdev(काष्ठा nvme_ns_head *head)
अणु
	पूर्णांक ret;

	head->cdev_device.parent = &head->subsys->dev;
	ret = dev_set_name(&head->cdev_device, "ng%dn%d",
			   head->subsys->instance, head->instance);
	अगर (ret)
		वापस ret;
	ret = nvme_cdev_add(&head->cdev, &head->cdev_device,
			    &nvme_ns_head_chr_fops, THIS_MODULE);
	अगर (ret)
		kमुक्त_स्थिर(head->cdev_device.kobj.name);
	वापस ret;
पूर्ण

अटल व्योम nvme_requeue_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvme_ns_head *head =
		container_of(work, काष्ठा nvme_ns_head, requeue_work);
	काष्ठा bio *bio, *next;

	spin_lock_irq(&head->requeue_lock);
	next = bio_list_get(&head->requeue_list);
	spin_unlock_irq(&head->requeue_lock);

	जबतक ((bio = next) != शून्य) अणु
		next = bio->bi_next;
		bio->bi_next = शून्य;

		/*
		 * Reset disk to the mpath node and resubmit to select a new
		 * path.
		 */
		bio_set_dev(bio, head->disk->part0);
		submit_bio_noacct(bio);
	पूर्ण
पूर्ण

पूर्णांक nvme_mpath_alloc_disk(काष्ठा nvme_ctrl *ctrl, काष्ठा nvme_ns_head *head)
अणु
	काष्ठा request_queue *q;
	bool vwc = false;

	mutex_init(&head->lock);
	bio_list_init(&head->requeue_list);
	spin_lock_init(&head->requeue_lock);
	INIT_WORK(&head->requeue_work, nvme_requeue_work);

	/*
	 * Add a multipath node अगर the subप्रणालीs supports multiple controllers.
	 * We also करो this क्रम निजी namespaces as the namespace sharing data could
	 * change after a rescan.
	 */
	अगर (!(ctrl->subsys->cmic & NVME_CTRL_CMIC_MULTI_CTRL) || !multipath)
		वापस 0;

	q = blk_alloc_queue(ctrl->numa_node);
	अगर (!q)
		जाओ out;
	blk_queue_flag_set(QUEUE_FLAG_NONROT, q);
	/* set to a शेष value क्रम 512 until disk is validated */
	blk_queue_logical_block_size(q, 512);
	blk_set_stacking_limits(&q->limits);

	/* we need to propagate up the VMC settings */
	अगर (ctrl->vwc & NVME_CTRL_VWC_PRESENT)
		vwc = true;
	blk_queue_ग_लिखो_cache(q, vwc, vwc);

	head->disk = alloc_disk(0);
	अगर (!head->disk)
		जाओ out_cleanup_queue;
	head->disk->fops = &nvme_ns_head_ops;
	head->disk->निजी_data = head;
	head->disk->queue = q;
	head->disk->flags = GENHD_FL_EXT_DEVT;
	प्र_लिखो(head->disk->disk_name, "nvme%dn%d",
			ctrl->subsys->instance, head->instance);
	वापस 0;

out_cleanup_queue:
	blk_cleanup_queue(q);
out:
	वापस -ENOMEM;
पूर्ण

अटल व्योम nvme_mpath_set_live(काष्ठा nvme_ns *ns)
अणु
	काष्ठा nvme_ns_head *head = ns->head;

	अगर (!head->disk)
		वापस;

	अगर (!test_and_set_bit(NVME_NSHEAD_DISK_LIVE, &head->flags)) अणु
		device_add_disk(&head->subsys->dev, head->disk,
				nvme_ns_id_attr_groups);
		nvme_add_ns_head_cdev(head);
	पूर्ण

	mutex_lock(&head->lock);
	अगर (nvme_path_is_optimized(ns)) अणु
		पूर्णांक node, srcu_idx;

		srcu_idx = srcu_पढ़ो_lock(&head->srcu);
		क्रम_each_node(node)
			__nvme_find_path(head, node);
		srcu_पढ़ो_unlock(&head->srcu, srcu_idx);
	पूर्ण
	mutex_unlock(&head->lock);

	synchronize_srcu(&head->srcu);
	kblockd_schedule_work(&head->requeue_work);
पूर्ण

अटल पूर्णांक nvme_parse_ana_log(काष्ठा nvme_ctrl *ctrl, व्योम *data,
		पूर्णांक (*cb)(काष्ठा nvme_ctrl *ctrl, काष्ठा nvme_ana_group_desc *,
			व्योम *))
अणु
	व्योम *base = ctrl->ana_log_buf;
	माप_प्रकार offset = माप(काष्ठा nvme_ana_rsp_hdr);
	पूर्णांक error, i;

	lockdep_निश्चित_held(&ctrl->ana_lock);

	क्रम (i = 0; i < le16_to_cpu(ctrl->ana_log_buf->ngrps); i++) अणु
		काष्ठा nvme_ana_group_desc *desc = base + offset;
		u32 nr_nsids;
		माप_प्रकार nsid_buf_size;

		अगर (WARN_ON_ONCE(offset > ctrl->ana_log_size - माप(*desc)))
			वापस -EINVAL;

		nr_nsids = le32_to_cpu(desc->nnsids);
		nsid_buf_size = nr_nsids * माप(__le32);

		अगर (WARN_ON_ONCE(desc->grpid == 0))
			वापस -EINVAL;
		अगर (WARN_ON_ONCE(le32_to_cpu(desc->grpid) > ctrl->anagrpmax))
			वापस -EINVAL;
		अगर (WARN_ON_ONCE(desc->state == 0))
			वापस -EINVAL;
		अगर (WARN_ON_ONCE(desc->state > NVME_ANA_CHANGE))
			वापस -EINVAL;

		offset += माप(*desc);
		अगर (WARN_ON_ONCE(offset > ctrl->ana_log_size - nsid_buf_size))
			वापस -EINVAL;

		error = cb(ctrl, desc, data);
		अगर (error)
			वापस error;

		offset += nsid_buf_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत bool nvme_state_is_live(क्रमागत nvme_ana_state state)
अणु
	वापस state == NVME_ANA_OPTIMIZED || state == NVME_ANA_NONOPTIMIZED;
पूर्ण

अटल व्योम nvme_update_ns_ana_state(काष्ठा nvme_ana_group_desc *desc,
		काष्ठा nvme_ns *ns)
अणु
	ns->ana_grpid = le32_to_cpu(desc->grpid);
	ns->ana_state = desc->state;
	clear_bit(NVME_NS_ANA_PENDING, &ns->flags);

	अगर (nvme_state_is_live(ns->ana_state))
		nvme_mpath_set_live(ns);
पूर्ण

अटल पूर्णांक nvme_update_ana_state(काष्ठा nvme_ctrl *ctrl,
		काष्ठा nvme_ana_group_desc *desc, व्योम *data)
अणु
	u32 nr_nsids = le32_to_cpu(desc->nnsids), n = 0;
	अचिन्हित *nr_change_groups = data;
	काष्ठा nvme_ns *ns;

	dev_dbg(ctrl->device, "ANA group %d: %s.\n",
			le32_to_cpu(desc->grpid),
			nvme_ana_state_names[desc->state]);

	अगर (desc->state == NVME_ANA_CHANGE)
		(*nr_change_groups)++;

	अगर (!nr_nsids)
		वापस 0;

	करोwn_पढ़ो(&ctrl->namespaces_rwsem);
	list_क्रम_each_entry(ns, &ctrl->namespaces, list) अणु
		अचिन्हित nsid = le32_to_cpu(desc->nsids[n]);

		अगर (ns->head->ns_id < nsid)
			जारी;
		अगर (ns->head->ns_id == nsid)
			nvme_update_ns_ana_state(desc, ns);
		अगर (++n == nr_nsids)
			अवरोध;
	पूर्ण
	up_पढ़ो(&ctrl->namespaces_rwsem);
	वापस 0;
पूर्ण

अटल पूर्णांक nvme_पढ़ो_ana_log(काष्ठा nvme_ctrl *ctrl)
अणु
	u32 nr_change_groups = 0;
	पूर्णांक error;

	mutex_lock(&ctrl->ana_lock);
	error = nvme_get_log(ctrl, NVME_NSID_ALL, NVME_LOG_ANA, 0, NVME_CSI_NVM,
			ctrl->ana_log_buf, ctrl->ana_log_size, 0);
	अगर (error) अणु
		dev_warn(ctrl->device, "Failed to get ANA log: %d\n", error);
		जाओ out_unlock;
	पूर्ण

	error = nvme_parse_ana_log(ctrl, &nr_change_groups,
			nvme_update_ana_state);
	अगर (error)
		जाओ out_unlock;

	/*
	 * In theory we should have an ANATT समयr per group as they might enter
	 * the change state at dअगरferent बार.  But that is a lot of overhead
	 * just to protect against a target that keeps entering new changes
	 * states जबतक never finishing previous ones.  But we'll still
	 * eventually समय out once all groups are in change state, so this
	 * isn't a big deal.
	 *
	 * We also द्विगुन the ANATT value to provide some slack क्रम transports
	 * or AEN processing overhead.
	 */
	अगर (nr_change_groups)
		mod_समयr(&ctrl->anatt_समयr, ctrl->anatt * HZ * 2 + jअगरfies);
	अन्यथा
		del_समयr_sync(&ctrl->anatt_समयr);
out_unlock:
	mutex_unlock(&ctrl->ana_lock);
	वापस error;
पूर्ण

अटल व्योम nvme_ana_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvme_ctrl *ctrl = container_of(work, काष्ठा nvme_ctrl, ana_work);

	अगर (ctrl->state != NVME_CTRL_LIVE)
		वापस;

	nvme_पढ़ो_ana_log(ctrl);
पूर्ण

अटल व्योम nvme_anatt_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा nvme_ctrl *ctrl = from_समयr(ctrl, t, anatt_समयr);

	dev_info(ctrl->device, "ANATT timeout, resetting controller.\n");
	nvme_reset_ctrl(ctrl);
पूर्ण

व्योम nvme_mpath_stop(काष्ठा nvme_ctrl *ctrl)
अणु
	अगर (!nvme_ctrl_use_ana(ctrl))
		वापस;
	del_समयr_sync(&ctrl->anatt_समयr);
	cancel_work_sync(&ctrl->ana_work);
पूर्ण

#घोषणा SUBSYS_ATTR_RW(_name, _mode, _show, _store)  \
	काष्ठा device_attribute subsys_attr_##_name =	\
		__ATTR(_name, _mode, _show, _store)

अटल स्थिर अक्षर *nvme_iopolicy_names[] = अणु
	[NVME_IOPOLICY_NUMA]	= "numa",
	[NVME_IOPOLICY_RR]	= "round-robin",
पूर्ण;

अटल sमाप_प्रकार nvme_subsys_iopolicy_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nvme_subप्रणाली *subsys =
		container_of(dev, काष्ठा nvme_subप्रणाली, dev);

	वापस sysfs_emit(buf, "%s\n",
			  nvme_iopolicy_names[READ_ONCE(subsys->iopolicy)]);
पूर्ण

अटल sमाप_प्रकार nvme_subsys_iopolicy_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nvme_subप्रणाली *subsys =
		container_of(dev, काष्ठा nvme_subप्रणाली, dev);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(nvme_iopolicy_names); i++) अणु
		अगर (sysfs_streq(buf, nvme_iopolicy_names[i])) अणु
			WRITE_ONCE(subsys->iopolicy, i);
			वापस count;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण
SUBSYS_ATTR_RW(iopolicy, S_IRUGO | S_IWUSR,
		      nvme_subsys_iopolicy_show, nvme_subsys_iopolicy_store);

अटल sमाप_प्रकार ana_grpid_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%d\n", nvme_get_ns_from_dev(dev)->ana_grpid);
पूर्ण
DEVICE_ATTR_RO(ana_grpid);

अटल sमाप_प्रकार ana_state_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा nvme_ns *ns = nvme_get_ns_from_dev(dev);

	वापस sysfs_emit(buf, "%s\n", nvme_ana_state_names[ns->ana_state]);
पूर्ण
DEVICE_ATTR_RO(ana_state);

अटल पूर्णांक nvme_lookup_ana_group_desc(काष्ठा nvme_ctrl *ctrl,
		काष्ठा nvme_ana_group_desc *desc, व्योम *data)
अणु
	काष्ठा nvme_ana_group_desc *dst = data;

	अगर (desc->grpid != dst->grpid)
		वापस 0;

	*dst = *desc;
	वापस -ENXIO; /* just अवरोध out of the loop */
पूर्ण

व्योम nvme_mpath_add_disk(काष्ठा nvme_ns *ns, काष्ठा nvme_id_ns *id)
अणु
	अगर (nvme_ctrl_use_ana(ns->ctrl)) अणु
		काष्ठा nvme_ana_group_desc desc = अणु
			.grpid = id->anagrpid,
			.state = 0,
		पूर्ण;

		mutex_lock(&ns->ctrl->ana_lock);
		ns->ana_grpid = le32_to_cpu(id->anagrpid);
		nvme_parse_ana_log(ns->ctrl, &desc, nvme_lookup_ana_group_desc);
		mutex_unlock(&ns->ctrl->ana_lock);
		अगर (desc.state) अणु
			/* found the group desc: update */
			nvme_update_ns_ana_state(&desc, ns);
		पूर्ण अन्यथा अणु
			/* group desc not found: trigger a re-पढ़ो */
			set_bit(NVME_NS_ANA_PENDING, &ns->flags);
			queue_work(nvme_wq, &ns->ctrl->ana_work);
		पूर्ण
	पूर्ण अन्यथा अणु
		ns->ana_state = NVME_ANA_OPTIMIZED;
		nvme_mpath_set_live(ns);
	पूर्ण

	अगर (blk_queue_stable_ग_लिखोs(ns->queue) && ns->head->disk)
		blk_queue_flag_set(QUEUE_FLAG_STABLE_WRITES,
				   ns->head->disk->queue);
#अगर_घोषित CONFIG_BLK_DEV_ZONED
	अगर (blk_queue_is_zoned(ns->queue) && ns->head->disk)
		ns->head->disk->queue->nr_zones = ns->queue->nr_zones;
#पूर्ण_अगर
पूर्ण

व्योम nvme_mpath_हटाओ_disk(काष्ठा nvme_ns_head *head)
अणु
	अगर (!head->disk)
		वापस;
	अगर (head->disk->flags & GENHD_FL_UP) अणु
		nvme_cdev_del(&head->cdev, &head->cdev_device);
		del_gendisk(head->disk);
	पूर्ण
	blk_set_queue_dying(head->disk->queue);
	/* make sure all pending bios are cleaned up */
	kblockd_schedule_work(&head->requeue_work);
	flush_work(&head->requeue_work);
	blk_cleanup_queue(head->disk->queue);
	अगर (!test_bit(NVME_NSHEAD_DISK_LIVE, &head->flags)) अणु
		/*
		 * अगर device_add_disk wasn't called, prevent
		 * disk release to put a bogus reference on the
		 * request queue
		 */
		head->disk->queue = शून्य;
	पूर्ण
	put_disk(head->disk);
पूर्ण

व्योम nvme_mpath_init_ctrl(काष्ठा nvme_ctrl *ctrl)
अणु
	mutex_init(&ctrl->ana_lock);
	समयr_setup(&ctrl->anatt_समयr, nvme_anatt_समयout, 0);
	INIT_WORK(&ctrl->ana_work, nvme_ana_work);
पूर्ण

पूर्णांक nvme_mpath_init_identअगरy(काष्ठा nvme_ctrl *ctrl, काष्ठा nvme_id_ctrl *id)
अणु
	माप_प्रकार max_transfer_size = ctrl->max_hw_sectors << SECTOR_SHIFT;
	माप_प्रकार ana_log_size;
	पूर्णांक error = 0;

	/* check अगर multipath is enabled and we have the capability */
	अगर (!multipath || !ctrl->subsys ||
	    !(ctrl->subsys->cmic & NVME_CTRL_CMIC_ANA))
		वापस 0;

	ctrl->anacap = id->anacap;
	ctrl->anatt = id->anatt;
	ctrl->nanagrpid = le32_to_cpu(id->nanagrpid);
	ctrl->anagrpmax = le32_to_cpu(id->anagrpmax);

	ana_log_size = माप(काष्ठा nvme_ana_rsp_hdr) +
		ctrl->nanagrpid * माप(काष्ठा nvme_ana_group_desc) +
		ctrl->max_namespaces * माप(__le32);
	अगर (ana_log_size > max_transfer_size) अणु
		dev_err(ctrl->device,
			"ANA log page size (%zd) larger than MDTS (%zd).\n",
			ana_log_size, max_transfer_size);
		dev_err(ctrl->device, "disabling ANA support.\n");
		जाओ out_uninit;
	पूर्ण
	अगर (ana_log_size > ctrl->ana_log_size) अणु
		nvme_mpath_stop(ctrl);
		kमुक्त(ctrl->ana_log_buf);
		ctrl->ana_log_buf = kदो_स्मृति(ana_log_size, GFP_KERNEL);
		अगर (!ctrl->ana_log_buf)
			वापस -ENOMEM;
	पूर्ण
	ctrl->ana_log_size = ana_log_size;
	error = nvme_पढ़ो_ana_log(ctrl);
	अगर (error)
		जाओ out_uninit;
	वापस 0;

out_uninit:
	nvme_mpath_uninit(ctrl);
	वापस error;
पूर्ण

व्योम nvme_mpath_uninit(काष्ठा nvme_ctrl *ctrl)
अणु
	kमुक्त(ctrl->ana_log_buf);
	ctrl->ana_log_buf = शून्य;
पूर्ण
