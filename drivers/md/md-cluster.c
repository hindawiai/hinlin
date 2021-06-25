<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015, SUSE
 */


#समावेश <linux/module.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/dlm.h>
#समावेश <linux/sched.h>
#समावेश <linux/raid/md_p.h>
#समावेश "md.h"
#समावेश "md-bitmap.h"
#समावेश "md-cluster.h"

#घोषणा LVB_SIZE	64
#घोषणा NEW_DEV_TIMEOUT 5000

काष्ठा dlm_lock_resource अणु
	dlm_lockspace_t *ls;
	काष्ठा dlm_lksb lksb;
	अक्षर *name; /* lock name. */
	uपूर्णांक32_t flags; /* flags to pass to dlm_lock() */
	रुको_queue_head_t sync_locking; /* रुको queue क्रम synchronized locking */
	bool sync_locking_करोne;
	व्योम (*bast)(व्योम *arg, पूर्णांक mode); /* blocking AST function poपूर्णांकer*/
	काष्ठा mddev *mddev; /* poपूर्णांकing back to mddev. */
	पूर्णांक mode;
पूर्ण;

काष्ठा resync_info अणु
	__le64 lo;
	__le64 hi;
पूर्ण;

/* md_cluster_info flags */
#घोषणा		MD_CLUSTER_WAITING_FOR_NEWDISK		1
#घोषणा		MD_CLUSTER_SUSPEND_READ_BALANCING	2
#घोषणा		MD_CLUSTER_BEGIN_JOIN_CLUSTER		3

/* Lock the send communication. This is करोne through
 * bit manipulation as opposed to a mutex in order to
 * accomodate lock and hold. See next comment.
 */
#घोषणा		MD_CLUSTER_SEND_LOCK			4
/* If cluster operations (such as adding a disk) must lock the
 * communication channel, so as to perक्रमm extra operations
 * (update metadata) and no other operation is allowed on the
 * MD. Token needs to be locked and held until the operation
 * completes witha md_update_sb(), which would eventually release
 * the lock.
 */
#घोषणा		MD_CLUSTER_SEND_LOCKED_ALREADY		5
/* We should receive message after node joined cluster and
 * set up all the related infos such as biपंचांगap and personality */
#घोषणा		MD_CLUSTER_ALREADY_IN_CLUSTER		6
#घोषणा		MD_CLUSTER_PENDING_RECV_EVENT		7
#घोषणा 	MD_CLUSTER_HOLDING_MUTEX_FOR_RECVD		8

काष्ठा md_cluster_info अणु
	काष्ठा mddev *mddev; /* the md device which md_cluster_info beदीर्घs to */
	/* dlm lock space and resources क्रम clustered raid. */
	dlm_lockspace_t *lockspace;
	पूर्णांक slot_number;
	काष्ठा completion completion;
	काष्ठा mutex recv_mutex;
	काष्ठा dlm_lock_resource *biपंचांगap_lockres;
	काष्ठा dlm_lock_resource **other_biपंचांगap_lockres;
	काष्ठा dlm_lock_resource *resync_lockres;
	काष्ठा list_head suspend_list;

	spinlock_t suspend_lock;
	/* record the region which ग_लिखो should be suspended */
	sector_t suspend_lo;
	sector_t suspend_hi;
	पूर्णांक suspend_from; /* the slot which broadcast suspend_lo/hi */

	काष्ठा md_thपढ़ो *recovery_thपढ़ो;
	अचिन्हित दीर्घ recovery_map;
	/* communication loc resources */
	काष्ठा dlm_lock_resource *ack_lockres;
	काष्ठा dlm_lock_resource *message_lockres;
	काष्ठा dlm_lock_resource *token_lockres;
	काष्ठा dlm_lock_resource *no_new_dev_lockres;
	काष्ठा md_thपढ़ो *recv_thपढ़ो;
	काष्ठा completion newdisk_completion;
	रुको_queue_head_t रुको;
	अचिन्हित दीर्घ state;
	/* record the region in RESYNCING message */
	sector_t sync_low;
	sector_t sync_hi;
पूर्ण;

क्रमागत msg_type अणु
	METADATA_UPDATED = 0,
	RESYNCING,
	NEWDISK,
	REMOVE,
	RE_ADD,
	BITMAP_NEEDS_SYNC,
	CHANGE_CAPACITY,
	BITMAP_RESIZE,
पूर्ण;

काष्ठा cluster_msg अणु
	__le32 type;
	__le32 slot;
	/* TODO: Unionize this क्रम smaller footprपूर्णांक */
	__le64 low;
	__le64 high;
	अक्षर uuid[16];
	__le32 raid_slot;
पूर्ण;

अटल व्योम sync_ast(व्योम *arg)
अणु
	काष्ठा dlm_lock_resource *res;

	res = arg;
	res->sync_locking_करोne = true;
	wake_up(&res->sync_locking);
पूर्ण

अटल पूर्णांक dlm_lock_sync(काष्ठा dlm_lock_resource *res, पूर्णांक mode)
अणु
	पूर्णांक ret = 0;

	ret = dlm_lock(res->ls, mode, &res->lksb,
			res->flags, res->name, म_माप(res->name),
			0, sync_ast, res, res->bast);
	अगर (ret)
		वापस ret;
	रुको_event(res->sync_locking, res->sync_locking_करोne);
	res->sync_locking_करोne = false;
	अगर (res->lksb.sb_status == 0)
		res->mode = mode;
	वापस res->lksb.sb_status;
पूर्ण

अटल पूर्णांक dlm_unlock_sync(काष्ठा dlm_lock_resource *res)
अणु
	वापस dlm_lock_sync(res, DLM_LOCK_NL);
पूर्ण

/*
 * An variation of dlm_lock_sync, which make lock request could
 * be पूर्णांकerrupted
 */
अटल पूर्णांक dlm_lock_sync_पूर्णांकerruptible(काष्ठा dlm_lock_resource *res, पूर्णांक mode,
				       काष्ठा mddev *mddev)
अणु
	पूर्णांक ret = 0;

	ret = dlm_lock(res->ls, mode, &res->lksb,
			res->flags, res->name, म_माप(res->name),
			0, sync_ast, res, res->bast);
	अगर (ret)
		वापस ret;

	रुको_event(res->sync_locking, res->sync_locking_करोne
				      || kthपढ़ो_should_stop()
				      || test_bit(MD_CLOSING, &mddev->flags));
	अगर (!res->sync_locking_करोne) अणु
		/*
		 * the convert queue contains the lock request when request is
		 * पूर्णांकerrupted, and sync_ast could still be run, so need to
		 * cancel the request and reset completion
		 */
		ret = dlm_unlock(res->ls, res->lksb.sb_lkid, DLM_LKF_CANCEL,
			&res->lksb, res);
		res->sync_locking_करोne = false;
		अगर (unlikely(ret != 0))
			pr_info("failed to cancel previous lock request "
				 "%s return %d\n", res->name, ret);
		वापस -EPERM;
	पूर्ण अन्यथा
		res->sync_locking_करोne = false;
	अगर (res->lksb.sb_status == 0)
		res->mode = mode;
	वापस res->lksb.sb_status;
पूर्ण

अटल काष्ठा dlm_lock_resource *lockres_init(काष्ठा mddev *mddev,
		अक्षर *name, व्योम (*bastfn)(व्योम *arg, पूर्णांक mode), पूर्णांक with_lvb)
अणु
	काष्ठा dlm_lock_resource *res = शून्य;
	पूर्णांक ret, namelen;
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;

	res = kzalloc(माप(काष्ठा dlm_lock_resource), GFP_KERNEL);
	अगर (!res)
		वापस शून्य;
	init_रुकोqueue_head(&res->sync_locking);
	res->sync_locking_करोne = false;
	res->ls = cinfo->lockspace;
	res->mddev = mddev;
	res->mode = DLM_LOCK_IV;
	namelen = म_माप(name);
	res->name = kzalloc(namelen + 1, GFP_KERNEL);
	अगर (!res->name) अणु
		pr_err("md-cluster: Unable to allocate resource name for resource %s\n", name);
		जाओ out_err;
	पूर्ण
	strlcpy(res->name, name, namelen + 1);
	अगर (with_lvb) अणु
		res->lksb.sb_lvbptr = kzalloc(LVB_SIZE, GFP_KERNEL);
		अगर (!res->lksb.sb_lvbptr) अणु
			pr_err("md-cluster: Unable to allocate LVB for resource %s\n", name);
			जाओ out_err;
		पूर्ण
		res->flags = DLM_LKF_VALBLK;
	पूर्ण

	अगर (bastfn)
		res->bast = bastfn;

	res->flags |= DLM_LKF_EXPEDITE;

	ret = dlm_lock_sync(res, DLM_LOCK_NL);
	अगर (ret) अणु
		pr_err("md-cluster: Unable to lock NL on new lock resource %s\n", name);
		जाओ out_err;
	पूर्ण
	res->flags &= ~DLM_LKF_EXPEDITE;
	res->flags |= DLM_LKF_CONVERT;

	वापस res;
out_err:
	kमुक्त(res->lksb.sb_lvbptr);
	kमुक्त(res->name);
	kमुक्त(res);
	वापस शून्य;
पूर्ण

अटल व्योम lockres_मुक्त(काष्ठा dlm_lock_resource *res)
अणु
	पूर्णांक ret = 0;

	अगर (!res)
		वापस;

	/*
	 * use FORCEUNLOCK flag, so we can unlock even the lock is on the
	 * रुकोing or convert queue
	 */
	ret = dlm_unlock(res->ls, res->lksb.sb_lkid, DLM_LKF_FORCEUNLOCK,
		&res->lksb, res);
	अगर (unlikely(ret != 0))
		pr_err("failed to unlock %s return %d\n", res->name, ret);
	अन्यथा
		रुको_event(res->sync_locking, res->sync_locking_करोne);

	kमुक्त(res->name);
	kमुक्त(res->lksb.sb_lvbptr);
	kमुक्त(res);
पूर्ण

अटल व्योम add_resync_info(काष्ठा dlm_lock_resource *lockres,
			    sector_t lo, sector_t hi)
अणु
	काष्ठा resync_info *ri;

	ri = (काष्ठा resync_info *)lockres->lksb.sb_lvbptr;
	ri->lo = cpu_to_le64(lo);
	ri->hi = cpu_to_le64(hi);
पूर्ण

अटल पूर्णांक पढ़ो_resync_info(काष्ठा mddev *mddev,
			    काष्ठा dlm_lock_resource *lockres)
अणु
	काष्ठा resync_info ri;
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;
	पूर्णांक ret = 0;

	dlm_lock_sync(lockres, DLM_LOCK_CR);
	स_नकल(&ri, lockres->lksb.sb_lvbptr, माप(काष्ठा resync_info));
	अगर (le64_to_cpu(ri.hi) > 0) अणु
		cinfo->suspend_hi = le64_to_cpu(ri.hi);
		cinfo->suspend_lo = le64_to_cpu(ri.lo);
		ret = 1;
	पूर्ण
	dlm_unlock_sync(lockres);
	वापस ret;
पूर्ण

अटल व्योम recover_biपंचांगaps(काष्ठा md_thपढ़ो *thपढ़ो)
अणु
	काष्ठा mddev *mddev = thपढ़ो->mddev;
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;
	काष्ठा dlm_lock_resource *bm_lockres;
	अक्षर str[64];
	पूर्णांक slot, ret;
	sector_t lo, hi;

	जबतक (cinfo->recovery_map) अणु
		slot = fls64((u64)cinfo->recovery_map) - 1;

		snम_लिखो(str, 64, "bitmap%04d", slot);
		bm_lockres = lockres_init(mddev, str, शून्य, 1);
		अगर (!bm_lockres) अणु
			pr_err("md-cluster: Cannot initialize bitmaps\n");
			जाओ clear_bit;
		पूर्ण

		ret = dlm_lock_sync_पूर्णांकerruptible(bm_lockres, DLM_LOCK_PW, mddev);
		अगर (ret) अणु
			pr_err("md-cluster: Could not DLM lock %s: %d\n",
					str, ret);
			जाओ clear_bit;
		पूर्ण
		ret = md_biपंचांगap_copy_from_slot(mddev, slot, &lo, &hi, true);
		अगर (ret) अणु
			pr_err("md-cluster: Could not copy data from bitmap %d\n", slot);
			जाओ clear_bit;
		पूर्ण

		/* Clear suspend_area associated with the biपंचांगap */
		spin_lock_irq(&cinfo->suspend_lock);
		cinfo->suspend_hi = 0;
		cinfo->suspend_lo = 0;
		cinfo->suspend_from = -1;
		spin_unlock_irq(&cinfo->suspend_lock);

		/* Kick off a reshape अगर needed */
		अगर (test_bit(MD_RESYNCING_REMOTE, &mddev->recovery) &&
		    test_bit(MD_RECOVERY_RESHAPE, &mddev->recovery) &&
		    mddev->reshape_position != MaxSector)
			md_wakeup_thपढ़ो(mddev->sync_thपढ़ो);

		अगर (hi > 0) अणु
			अगर (lo < mddev->recovery_cp)
				mddev->recovery_cp = lo;
			/* wake up thपढ़ो to जारी resync in हाल resync
			 * is not finished */
			अगर (mddev->recovery_cp != MaxSector) अणु
				/*
				 * clear the REMOTE flag since we will launch
				 * resync thपढ़ो in current node.
				 */
				clear_bit(MD_RESYNCING_REMOTE,
					  &mddev->recovery);
				set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
				md_wakeup_thपढ़ो(mddev->thपढ़ो);
			पूर्ण
		पूर्ण
clear_bit:
		lockres_मुक्त(bm_lockres);
		clear_bit(slot, &cinfo->recovery_map);
	पूर्ण
पूर्ण

अटल व्योम recover_prep(व्योम *arg)
अणु
	काष्ठा mddev *mddev = arg;
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;
	set_bit(MD_CLUSTER_SUSPEND_READ_BALANCING, &cinfo->state);
पूर्ण

अटल व्योम __recover_slot(काष्ठा mddev *mddev, पूर्णांक slot)
अणु
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;

	set_bit(slot, &cinfo->recovery_map);
	अगर (!cinfo->recovery_thपढ़ो) अणु
		cinfo->recovery_thपढ़ो = md_रेजिस्टर_thपढ़ो(recover_biपंचांगaps,
				mddev, "recover");
		अगर (!cinfo->recovery_thपढ़ो) अणु
			pr_warn("md-cluster: Could not create recovery thread\n");
			वापस;
		पूर्ण
	पूर्ण
	md_wakeup_thपढ़ो(cinfo->recovery_thपढ़ो);
पूर्ण

अटल व्योम recover_slot(व्योम *arg, काष्ठा dlm_slot *slot)
अणु
	काष्ठा mddev *mddev = arg;
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;

	pr_info("md-cluster: %s Node %d/%d down. My slot: %d. Initiating recovery.\n",
			mddev->biपंचांगap_info.cluster_name,
			slot->nodeid, slot->slot,
			cinfo->slot_number);
	/* deduct one since dlm slot starts from one जबतक the num of
	 * cluster-md begins with 0 */
	__recover_slot(mddev, slot->slot - 1);
पूर्ण

अटल व्योम recover_करोne(व्योम *arg, काष्ठा dlm_slot *slots,
		पूर्णांक num_slots, पूर्णांक our_slot,
		uपूर्णांक32_t generation)
अणु
	काष्ठा mddev *mddev = arg;
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;

	cinfo->slot_number = our_slot;
	/* completion is only need to be complete when node join cluster,
	 * it करोesn't need to run during another node's failure */
	अगर (test_bit(MD_CLUSTER_BEGIN_JOIN_CLUSTER, &cinfo->state)) अणु
		complete(&cinfo->completion);
		clear_bit(MD_CLUSTER_BEGIN_JOIN_CLUSTER, &cinfo->state);
	पूर्ण
	clear_bit(MD_CLUSTER_SUSPEND_READ_BALANCING, &cinfo->state);
पूर्ण

/* the ops is called when node join the cluster, and करो lock recovery
 * अगर node failure occurs */
अटल स्थिर काष्ठा dlm_lockspace_ops md_ls_ops = अणु
	.recover_prep = recover_prep,
	.recover_slot = recover_slot,
	.recover_करोne = recover_करोne,
पूर्ण;

/*
 * The BAST function क्रम the ack lock resource
 * This function wakes up the receive thपढ़ो in
 * order to receive and process the message.
 */
अटल व्योम ack_bast(व्योम *arg, पूर्णांक mode)
अणु
	काष्ठा dlm_lock_resource *res = arg;
	काष्ठा md_cluster_info *cinfo = res->mddev->cluster_info;

	अगर (mode == DLM_LOCK_EX) अणु
		अगर (test_bit(MD_CLUSTER_ALREADY_IN_CLUSTER, &cinfo->state))
			md_wakeup_thपढ़ो(cinfo->recv_thपढ़ो);
		अन्यथा
			set_bit(MD_CLUSTER_PENDING_RECV_EVENT, &cinfo->state);
	पूर्ण
पूर्ण

अटल व्योम हटाओ_suspend_info(काष्ठा mddev *mddev, पूर्णांक slot)
अणु
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;
	mddev->pers->quiesce(mddev, 1);
	spin_lock_irq(&cinfo->suspend_lock);
	cinfo->suspend_hi = 0;
	cinfo->suspend_lo = 0;
	spin_unlock_irq(&cinfo->suspend_lock);
	mddev->pers->quiesce(mddev, 0);
पूर्ण

अटल व्योम process_suspend_info(काष्ठा mddev *mddev,
		पूर्णांक slot, sector_t lo, sector_t hi)
अणु
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;
	काष्ठा mdp_superblock_1 *sb = शून्य;
	काष्ठा md_rdev *rdev;

	अगर (!hi) अणु
		/*
		 * clear the REMOTE flag since resync or recovery is finished
		 * in remote node.
		 */
		clear_bit(MD_RESYNCING_REMOTE, &mddev->recovery);
		हटाओ_suspend_info(mddev, slot);
		set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
		md_wakeup_thपढ़ो(mddev->thपढ़ो);
		वापस;
	पूर्ण

	rdev_क्रम_each(rdev, mddev)
		अगर (rdev->raid_disk > -1 && !test_bit(Faulty, &rdev->flags)) अणु
			sb = page_address(rdev->sb_page);
			अवरोध;
		पूर्ण

	/*
	 * The biपंचांगaps are not same क्रम dअगरferent nodes
	 * अगर RESYNCING is happening in one node, then
	 * the node which received the RESYNCING message
	 * probably will perक्रमm resync with the region
	 * [lo, hi] again, so we could reduce resync समय
	 * a lot अगर we can ensure that the biपंचांगaps among
	 * dअगरferent nodes are match up well.
	 *
	 * sync_low/hi is used to record the region which
	 * arrived in the previous RESYNCING message,
	 *
	 * Call md_biपंचांगap_sync_with_cluster to clear NEEDED_MASK
	 * and set RESYNC_MASK since  resync thपढ़ो is running
	 * in another node, so we करोn't need to करो the resync
	 * again with the same section.
	 *
	 * Skip md_biपंचांगap_sync_with_cluster in हाल reshape
	 * happening, because reshaping region is small and
	 * we करोn't want to trigger lots of WARN.
	 */
	अगर (sb && !(le32_to_cpu(sb->feature_map) & MD_FEATURE_RESHAPE_ACTIVE))
		md_biपंचांगap_sync_with_cluster(mddev, cinfo->sync_low,
					    cinfo->sync_hi, lo, hi);
	cinfo->sync_low = lo;
	cinfo->sync_hi = hi;

	mddev->pers->quiesce(mddev, 1);
	spin_lock_irq(&cinfo->suspend_lock);
	cinfo->suspend_from = slot;
	cinfo->suspend_lo = lo;
	cinfo->suspend_hi = hi;
	spin_unlock_irq(&cinfo->suspend_lock);
	mddev->pers->quiesce(mddev, 0);
पूर्ण

अटल व्योम process_add_new_disk(काष्ठा mddev *mddev, काष्ठा cluster_msg *cmsg)
अणु
	अक्षर disk_uuid[64];
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;
	अक्षर event_name[] = "EVENT=ADD_DEVICE";
	अक्षर raid_slot[16];
	अक्षर *envp[] = अणुevent_name, disk_uuid, raid_slot, शून्यपूर्ण;
	पूर्णांक len;

	len = snम_लिखो(disk_uuid, 64, "DEVICE_UUID=");
	प्र_लिखो(disk_uuid + len, "%pU", cmsg->uuid);
	snम_लिखो(raid_slot, 16, "RAID_DISK=%d", le32_to_cpu(cmsg->raid_slot));
	pr_info("%s:%d Sending kobject change with %s and %s\n", __func__, __LINE__, disk_uuid, raid_slot);
	init_completion(&cinfo->newdisk_completion);
	set_bit(MD_CLUSTER_WAITING_FOR_NEWDISK, &cinfo->state);
	kobject_uevent_env(&disk_to_dev(mddev->gendisk)->kobj, KOBJ_CHANGE, envp);
	रुको_क्रम_completion_समयout(&cinfo->newdisk_completion,
			NEW_DEV_TIMEOUT);
	clear_bit(MD_CLUSTER_WAITING_FOR_NEWDISK, &cinfo->state);
पूर्ण


अटल व्योम process_metadata_update(काष्ठा mddev *mddev, काष्ठा cluster_msg *msg)
अणु
	पूर्णांक got_lock = 0;
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;
	mddev->good_device_nr = le32_to_cpu(msg->raid_slot);

	dlm_lock_sync(cinfo->no_new_dev_lockres, DLM_LOCK_CR);
	रुको_event(mddev->thपढ़ो->wqueue,
		   (got_lock = mddev_trylock(mddev)) ||
		    test_bit(MD_CLUSTER_HOLDING_MUTEX_FOR_RECVD, &cinfo->state));
	md_reload_sb(mddev, mddev->good_device_nr);
	अगर (got_lock)
		mddev_unlock(mddev);
पूर्ण

अटल व्योम process_हटाओ_disk(काष्ठा mddev *mddev, काष्ठा cluster_msg *msg)
अणु
	काष्ठा md_rdev *rdev;

	rcu_पढ़ो_lock();
	rdev = md_find_rdev_nr_rcu(mddev, le32_to_cpu(msg->raid_slot));
	अगर (rdev) अणु
		set_bit(ClusterRemove, &rdev->flags);
		set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
		md_wakeup_thपढ़ो(mddev->thपढ़ो);
	पूर्ण
	अन्यथा
		pr_warn("%s: %d Could not find disk(%d) to REMOVE\n",
			__func__, __LINE__, le32_to_cpu(msg->raid_slot));
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम process_पढ़ोd_disk(काष्ठा mddev *mddev, काष्ठा cluster_msg *msg)
अणु
	काष्ठा md_rdev *rdev;

	rcu_पढ़ो_lock();
	rdev = md_find_rdev_nr_rcu(mddev, le32_to_cpu(msg->raid_slot));
	अगर (rdev && test_bit(Faulty, &rdev->flags))
		clear_bit(Faulty, &rdev->flags);
	अन्यथा
		pr_warn("%s: %d Could not find disk(%d) which is faulty",
			__func__, __LINE__, le32_to_cpu(msg->raid_slot));
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक process_recvd_msg(काष्ठा mddev *mddev, काष्ठा cluster_msg *msg)
अणु
	पूर्णांक ret = 0;

	अगर (WARN(mddev->cluster_info->slot_number - 1 == le32_to_cpu(msg->slot),
		"node %d received it's own msg\n", le32_to_cpu(msg->slot)))
		वापस -1;
	चयन (le32_to_cpu(msg->type)) अणु
	हाल METADATA_UPDATED:
		process_metadata_update(mddev, msg);
		अवरोध;
	हाल CHANGE_CAPACITY:
		set_capacity_and_notअगरy(mddev->gendisk, mddev->array_sectors);
		अवरोध;
	हाल RESYNCING:
		set_bit(MD_RESYNCING_REMOTE, &mddev->recovery);
		process_suspend_info(mddev, le32_to_cpu(msg->slot),
				     le64_to_cpu(msg->low),
				     le64_to_cpu(msg->high));
		अवरोध;
	हाल NEWDISK:
		process_add_new_disk(mddev, msg);
		अवरोध;
	हाल REMOVE:
		process_हटाओ_disk(mddev, msg);
		अवरोध;
	हाल RE_ADD:
		process_पढ़ोd_disk(mddev, msg);
		अवरोध;
	हाल BITMAP_NEEDS_SYNC:
		__recover_slot(mddev, le32_to_cpu(msg->slot));
		अवरोध;
	हाल BITMAP_RESIZE:
		अगर (le64_to_cpu(msg->high) != mddev->pers->size(mddev, 0, 0))
			ret = md_biपंचांगap_resize(mddev->biपंचांगap,
					    le64_to_cpu(msg->high), 0, 0);
		अवरोध;
	शेष:
		ret = -1;
		pr_warn("%s:%d Received unknown message from %d\n",
			__func__, __LINE__, msg->slot);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * thपढ़ो क्रम receiving message
 */
अटल व्योम recv_daemon(काष्ठा md_thपढ़ो *thपढ़ो)
अणु
	काष्ठा md_cluster_info *cinfo = thपढ़ो->mddev->cluster_info;
	काष्ठा dlm_lock_resource *ack_lockres = cinfo->ack_lockres;
	काष्ठा dlm_lock_resource *message_lockres = cinfo->message_lockres;
	काष्ठा cluster_msg msg;
	पूर्णांक ret;

	mutex_lock(&cinfo->recv_mutex);
	/*get CR on Message*/
	अगर (dlm_lock_sync(message_lockres, DLM_LOCK_CR)) अणु
		pr_err("md/raid1:failed to get CR on MESSAGE\n");
		mutex_unlock(&cinfo->recv_mutex);
		वापस;
	पूर्ण

	/* पढ़ो lvb and wake up thपढ़ो to process this message_lockres */
	स_नकल(&msg, message_lockres->lksb.sb_lvbptr, माप(काष्ठा cluster_msg));
	ret = process_recvd_msg(thपढ़ो->mddev, &msg);
	अगर (ret)
		जाओ out;

	/*release CR on ack_lockres*/
	ret = dlm_unlock_sync(ack_lockres);
	अगर (unlikely(ret != 0))
		pr_info("unlock ack failed return %d\n", ret);
	/*up-convert to PR on message_lockres*/
	ret = dlm_lock_sync(message_lockres, DLM_LOCK_PR);
	अगर (unlikely(ret != 0))
		pr_info("lock PR on msg failed return %d\n", ret);
	/*get CR on ack_lockres again*/
	ret = dlm_lock_sync(ack_lockres, DLM_LOCK_CR);
	अगर (unlikely(ret != 0))
		pr_info("lock CR on ack failed return %d\n", ret);
out:
	/*release CR on message_lockres*/
	ret = dlm_unlock_sync(message_lockres);
	अगर (unlikely(ret != 0))
		pr_info("unlock msg failed return %d\n", ret);
	mutex_unlock(&cinfo->recv_mutex);
पूर्ण

/* lock_token()
 * Takes the lock on the TOKEN lock resource so no other
 * node can communicate जबतक the operation is underway.
 */
अटल पूर्णांक lock_token(काष्ठा md_cluster_info *cinfo)
अणु
	पूर्णांक error;

	error = dlm_lock_sync(cinfo->token_lockres, DLM_LOCK_EX);
	अगर (error) अणु
		pr_err("md-cluster(%s:%d): failed to get EX on TOKEN (%d)\n",
				__func__, __LINE__, error);
	पूर्ण अन्यथा अणु
		/* Lock the receive sequence */
		mutex_lock(&cinfo->recv_mutex);
	पूर्ण
	वापस error;
पूर्ण

/* lock_comm()
 * Sets the MD_CLUSTER_SEND_LOCK bit to lock the send channel.
 */
अटल पूर्णांक lock_comm(काष्ठा md_cluster_info *cinfo, bool mddev_locked)
अणु
	पूर्णांक rv, set_bit = 0;
	काष्ठा mddev *mddev = cinfo->mddev;

	/*
	 * If resync thपढ़ो run after raid1d thपढ़ो, then process_metadata_update
	 * could not जारी अगर raid1d held reconfig_mutex (and raid1d is blocked
	 * since another node alपढ़ोy got EX on Token and रुकोting the EX of Ack),
	 * so let resync wake up thपढ़ो in हाल flag is set.
	 */
	अगर (mddev_locked && !test_bit(MD_CLUSTER_HOLDING_MUTEX_FOR_RECVD,
				      &cinfo->state)) अणु
		rv = test_and_set_bit_lock(MD_CLUSTER_HOLDING_MUTEX_FOR_RECVD,
					      &cinfo->state);
		WARN_ON_ONCE(rv);
		md_wakeup_thपढ़ो(mddev->thपढ़ो);
		set_bit = 1;
	पूर्ण

	रुको_event(cinfo->रुको,
		   !test_and_set_bit(MD_CLUSTER_SEND_LOCK, &cinfo->state));
	rv = lock_token(cinfo);
	अगर (set_bit)
		clear_bit_unlock(MD_CLUSTER_HOLDING_MUTEX_FOR_RECVD, &cinfo->state);
	वापस rv;
पूर्ण

अटल व्योम unlock_comm(काष्ठा md_cluster_info *cinfo)
अणु
	WARN_ON(cinfo->token_lockres->mode != DLM_LOCK_EX);
	mutex_unlock(&cinfo->recv_mutex);
	dlm_unlock_sync(cinfo->token_lockres);
	clear_bit(MD_CLUSTER_SEND_LOCK, &cinfo->state);
	wake_up(&cinfo->रुको);
पूर्ण

/* __sendmsg()
 * This function perक्रमms the actual sending of the message. This function is
 * usually called after perक्रमming the encompassing operation
 * The function:
 * 1. Grअसल the message lockresource in EX mode
 * 2. Copies the message to the message LVB
 * 3. Downconverts message lockresource to CW
 * 4. Upconverts ack lock resource from CR to EX. This क्रमces the BAST on other nodes
 *    and the other nodes पढ़ो the message. The thपढ़ो will रुको here until all other
 *    nodes have released ack lock resource.
 * 5. Downconvert ack lockresource to CR
 */
अटल पूर्णांक __sendmsg(काष्ठा md_cluster_info *cinfo, काष्ठा cluster_msg *cmsg)
अणु
	पूर्णांक error;
	पूर्णांक slot = cinfo->slot_number - 1;

	cmsg->slot = cpu_to_le32(slot);
	/*get EX on Message*/
	error = dlm_lock_sync(cinfo->message_lockres, DLM_LOCK_EX);
	अगर (error) अणु
		pr_err("md-cluster: failed to get EX on MESSAGE (%d)\n", error);
		जाओ failed_message;
	पूर्ण

	स_नकल(cinfo->message_lockres->lksb.sb_lvbptr, (व्योम *)cmsg,
			माप(काष्ठा cluster_msg));
	/*करोwn-convert EX to CW on Message*/
	error = dlm_lock_sync(cinfo->message_lockres, DLM_LOCK_CW);
	अगर (error) अणु
		pr_err("md-cluster: failed to convert EX to CW on MESSAGE(%d)\n",
				error);
		जाओ failed_ack;
	पूर्ण

	/*up-convert CR to EX on Ack*/
	error = dlm_lock_sync(cinfo->ack_lockres, DLM_LOCK_EX);
	अगर (error) अणु
		pr_err("md-cluster: failed to convert CR to EX on ACK(%d)\n",
				error);
		जाओ failed_ack;
	पूर्ण

	/*करोwn-convert EX to CR on Ack*/
	error = dlm_lock_sync(cinfo->ack_lockres, DLM_LOCK_CR);
	अगर (error) अणु
		pr_err("md-cluster: failed to convert EX to CR on ACK(%d)\n",
				error);
		जाओ failed_ack;
	पूर्ण

failed_ack:
	error = dlm_unlock_sync(cinfo->message_lockres);
	अगर (unlikely(error != 0)) अणु
		pr_err("md-cluster: failed convert to NL on MESSAGE(%d)\n",
			error);
		/* in हाल the message can't be released due to some reason */
		जाओ failed_ack;
	पूर्ण
failed_message:
	वापस error;
पूर्ण

अटल पूर्णांक sendmsg(काष्ठा md_cluster_info *cinfo, काष्ठा cluster_msg *cmsg,
		   bool mddev_locked)
अणु
	पूर्णांक ret;

	ret = lock_comm(cinfo, mddev_locked);
	अगर (!ret) अणु
		ret = __sendmsg(cinfo, cmsg);
		unlock_comm(cinfo);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक gather_all_resync_info(काष्ठा mddev *mddev, पूर्णांक total_slots)
अणु
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;
	पूर्णांक i, ret = 0;
	काष्ठा dlm_lock_resource *bm_lockres;
	अक्षर str[64];
	sector_t lo, hi;


	क्रम (i = 0; i < total_slots; i++) अणु
		स_रखो(str, '\0', 64);
		snम_लिखो(str, 64, "bitmap%04d", i);
		bm_lockres = lockres_init(mddev, str, शून्य, 1);
		अगर (!bm_lockres)
			वापस -ENOMEM;
		अगर (i == (cinfo->slot_number - 1)) अणु
			lockres_मुक्त(bm_lockres);
			जारी;
		पूर्ण

		bm_lockres->flags |= DLM_LKF_NOQUEUE;
		ret = dlm_lock_sync(bm_lockres, DLM_LOCK_PW);
		अगर (ret == -EAGAIN) अणु
			अगर (पढ़ो_resync_info(mddev, bm_lockres)) अणु
				pr_info("%s:%d Resync[%llu..%llu] in progress on %d\n",
						__func__, __LINE__,
					(अचिन्हित दीर्घ दीर्घ) cinfo->suspend_lo,
					(अचिन्हित दीर्घ दीर्घ) cinfo->suspend_hi,
					i);
				cinfo->suspend_from = i;
			पूर्ण
			ret = 0;
			lockres_मुक्त(bm_lockres);
			जारी;
		पूर्ण
		अगर (ret) अणु
			lockres_मुक्त(bm_lockres);
			जाओ out;
		पूर्ण

		/* Read the disk biपंचांगap sb and check अगर it needs recovery */
		ret = md_biपंचांगap_copy_from_slot(mddev, i, &lo, &hi, false);
		अगर (ret) अणु
			pr_warn("md-cluster: Could not gather bitmaps from slot %d", i);
			lockres_मुक्त(bm_lockres);
			जारी;
		पूर्ण
		अगर ((hi > 0) && (lo < mddev->recovery_cp)) अणु
			set_bit(MD_RECOVERY_NEEDED, &mddev->recovery);
			mddev->recovery_cp = lo;
			md_check_recovery(mddev);
		पूर्ण

		lockres_मुक्त(bm_lockres);
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक join(काष्ठा mddev *mddev, पूर्णांक nodes)
अणु
	काष्ठा md_cluster_info *cinfo;
	पूर्णांक ret, ops_rv;
	अक्षर str[64];

	cinfo = kzalloc(माप(काष्ठा md_cluster_info), GFP_KERNEL);
	अगर (!cinfo)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&cinfo->suspend_list);
	spin_lock_init(&cinfo->suspend_lock);
	init_completion(&cinfo->completion);
	set_bit(MD_CLUSTER_BEGIN_JOIN_CLUSTER, &cinfo->state);
	init_रुकोqueue_head(&cinfo->रुको);
	mutex_init(&cinfo->recv_mutex);

	mddev->cluster_info = cinfo;
	cinfo->mddev = mddev;

	स_रखो(str, 0, 64);
	प्र_लिखो(str, "%pU", mddev->uuid);
	ret = dlm_new_lockspace(str, mddev->biपंचांगap_info.cluster_name,
				DLM_LSFL_FS, LVB_SIZE,
				&md_ls_ops, mddev, &ops_rv, &cinfo->lockspace);
	अगर (ret)
		जाओ err;
	रुको_क्रम_completion(&cinfo->completion);
	अगर (nodes < cinfo->slot_number) अणु
		pr_err("md-cluster: Slot allotted(%d) is greater than available slots(%d).",
			cinfo->slot_number, nodes);
		ret = -दुस्फल;
		जाओ err;
	पूर्ण
	/* Initiate the communication resources */
	ret = -ENOMEM;
	cinfo->recv_thपढ़ो = md_रेजिस्टर_thपढ़ो(recv_daemon, mddev, "cluster_recv");
	अगर (!cinfo->recv_thपढ़ो) अणु
		pr_err("md-cluster: cannot allocate memory for recv_thread!\n");
		जाओ err;
	पूर्ण
	cinfo->message_lockres = lockres_init(mddev, "message", शून्य, 1);
	अगर (!cinfo->message_lockres)
		जाओ err;
	cinfo->token_lockres = lockres_init(mddev, "token", शून्य, 0);
	अगर (!cinfo->token_lockres)
		जाओ err;
	cinfo->no_new_dev_lockres = lockres_init(mddev, "no-new-dev", शून्य, 0);
	अगर (!cinfo->no_new_dev_lockres)
		जाओ err;

	ret = dlm_lock_sync(cinfo->token_lockres, DLM_LOCK_EX);
	अगर (ret) अणु
		ret = -EAGAIN;
		pr_err("md-cluster: can't join cluster to avoid lock issue\n");
		जाओ err;
	पूर्ण
	cinfo->ack_lockres = lockres_init(mddev, "ack", ack_bast, 0);
	अगर (!cinfo->ack_lockres) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	/* get sync CR lock on ACK. */
	अगर (dlm_lock_sync(cinfo->ack_lockres, DLM_LOCK_CR))
		pr_err("md-cluster: failed to get a sync CR lock on ACK!(%d)\n",
				ret);
	dlm_unlock_sync(cinfo->token_lockres);
	/* get sync CR lock on no-new-dev. */
	अगर (dlm_lock_sync(cinfo->no_new_dev_lockres, DLM_LOCK_CR))
		pr_err("md-cluster: failed to get a sync CR lock on no-new-dev!(%d)\n", ret);


	pr_info("md-cluster: Joined cluster %s slot %d\n", str, cinfo->slot_number);
	snम_लिखो(str, 64, "bitmap%04d", cinfo->slot_number - 1);
	cinfo->biपंचांगap_lockres = lockres_init(mddev, str, शून्य, 1);
	अगर (!cinfo->biपंचांगap_lockres) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण
	अगर (dlm_lock_sync(cinfo->biपंचांगap_lockres, DLM_LOCK_PW)) अणु
		pr_err("Failed to get bitmap lock\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	cinfo->resync_lockres = lockres_init(mddev, "resync", शून्य, 0);
	अगर (!cinfo->resync_lockres) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	वापस 0;
err:
	set_bit(MD_CLUSTER_HOLDING_MUTEX_FOR_RECVD, &cinfo->state);
	md_unरेजिस्टर_thपढ़ो(&cinfo->recovery_thपढ़ो);
	md_unरेजिस्टर_thपढ़ो(&cinfo->recv_thपढ़ो);
	lockres_मुक्त(cinfo->message_lockres);
	lockres_मुक्त(cinfo->token_lockres);
	lockres_मुक्त(cinfo->ack_lockres);
	lockres_मुक्त(cinfo->no_new_dev_lockres);
	lockres_मुक्त(cinfo->resync_lockres);
	lockres_मुक्त(cinfo->biपंचांगap_lockres);
	अगर (cinfo->lockspace)
		dlm_release_lockspace(cinfo->lockspace, 2);
	mddev->cluster_info = शून्य;
	kमुक्त(cinfo);
	वापस ret;
पूर्ण

अटल व्योम load_biपंचांगaps(काष्ठा mddev *mddev, पूर्णांक total_slots)
अणु
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;

	/* load all the node's biपंचांगap info क्रम resync */
	अगर (gather_all_resync_info(mddev, total_slots))
		pr_err("md-cluster: failed to gather all resyn infos\n");
	set_bit(MD_CLUSTER_ALREADY_IN_CLUSTER, &cinfo->state);
	/* wake up recv thपढ़ो in हाल something need to be handled */
	अगर (test_and_clear_bit(MD_CLUSTER_PENDING_RECV_EVENT, &cinfo->state))
		md_wakeup_thपढ़ो(cinfo->recv_thपढ़ो);
पूर्ण

अटल व्योम resync_biपंचांगap(काष्ठा mddev *mddev)
अणु
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;
	काष्ठा cluster_msg cmsg = अणु0पूर्ण;
	पूर्णांक err;

	cmsg.type = cpu_to_le32(BITMAP_NEEDS_SYNC);
	err = sendmsg(cinfo, &cmsg, 1);
	अगर (err)
		pr_err("%s:%d: failed to send BITMAP_NEEDS_SYNC message (%d)\n",
			__func__, __LINE__, err);
पूर्ण

अटल व्योम unlock_all_biपंचांगaps(काष्ठा mddev *mddev);
अटल पूर्णांक leave(काष्ठा mddev *mddev)
अणु
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;

	अगर (!cinfo)
		वापस 0;

	/*
	 * BITMAP_NEEDS_SYNC message should be sent when node
	 * is leaving the cluster with dirty biपंचांगap, also we
	 * can only deliver it when dlm connection is available.
	 *
	 * Also, we should send BITMAP_NEEDS_SYNC message in
	 * हाल reshaping is पूर्णांकerrupted.
	 */
	अगर ((cinfo->slot_number > 0 && mddev->recovery_cp != MaxSector) ||
	    (mddev->reshape_position != MaxSector &&
	     test_bit(MD_CLOSING, &mddev->flags)))
		resync_biपंचांगap(mddev);

	set_bit(MD_CLUSTER_HOLDING_MUTEX_FOR_RECVD, &cinfo->state);
	md_unरेजिस्टर_thपढ़ो(&cinfo->recovery_thपढ़ो);
	md_unरेजिस्टर_thपढ़ो(&cinfo->recv_thपढ़ो);
	lockres_मुक्त(cinfo->message_lockres);
	lockres_मुक्त(cinfo->token_lockres);
	lockres_मुक्त(cinfo->ack_lockres);
	lockres_मुक्त(cinfo->no_new_dev_lockres);
	lockres_मुक्त(cinfo->resync_lockres);
	lockres_मुक्त(cinfo->biपंचांगap_lockres);
	unlock_all_biपंचांगaps(mddev);
	dlm_release_lockspace(cinfo->lockspace, 2);
	kमुक्त(cinfo);
	वापस 0;
पूर्ण

/* slot_number(): Returns the MD slot number to use
 * DLM starts the slot numbers from 1, wheras cluster-md
 * wants the number to be from zero, so we deduct one
 */
अटल पूर्णांक slot_number(काष्ठा mddev *mddev)
अणु
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;

	वापस cinfo->slot_number - 1;
पूर्ण

/*
 * Check अगर the communication is alपढ़ोy locked, अन्यथा lock the communication
 * channel.
 * If it is alपढ़ोy locked, token is in EX mode, and hence lock_token()
 * should not be called.
 */
अटल पूर्णांक metadata_update_start(काष्ठा mddev *mddev)
अणु
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;
	पूर्णांक ret;

	/*
	 * metadata_update_start is always called with the protection of
	 * reconfig_mutex, so set WAITING_FOR_TOKEN here.
	 */
	ret = test_and_set_bit_lock(MD_CLUSTER_HOLDING_MUTEX_FOR_RECVD,
				    &cinfo->state);
	WARN_ON_ONCE(ret);
	md_wakeup_thपढ़ो(mddev->thपढ़ो);

	रुको_event(cinfo->रुको,
		   !test_and_set_bit(MD_CLUSTER_SEND_LOCK, &cinfo->state) ||
		   test_and_clear_bit(MD_CLUSTER_SEND_LOCKED_ALREADY, &cinfo->state));

	/* If token is alपढ़ोy locked, वापस 0 */
	अगर (cinfo->token_lockres->mode == DLM_LOCK_EX) अणु
		clear_bit_unlock(MD_CLUSTER_HOLDING_MUTEX_FOR_RECVD, &cinfo->state);
		वापस 0;
	पूर्ण

	ret = lock_token(cinfo);
	clear_bit_unlock(MD_CLUSTER_HOLDING_MUTEX_FOR_RECVD, &cinfo->state);
	वापस ret;
पूर्ण

अटल पूर्णांक metadata_update_finish(काष्ठा mddev *mddev)
अणु
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;
	काष्ठा cluster_msg cmsg;
	काष्ठा md_rdev *rdev;
	पूर्णांक ret = 0;
	पूर्णांक raid_slot = -1;

	स_रखो(&cmsg, 0, माप(cmsg));
	cmsg.type = cpu_to_le32(METADATA_UPDATED);
	/* Pick up a good active device number to send.
	 */
	rdev_क्रम_each(rdev, mddev)
		अगर (rdev->raid_disk > -1 && !test_bit(Faulty, &rdev->flags)) अणु
			raid_slot = rdev->desc_nr;
			अवरोध;
		पूर्ण
	अगर (raid_slot >= 0) अणु
		cmsg.raid_slot = cpu_to_le32(raid_slot);
		ret = __sendmsg(cinfo, &cmsg);
	पूर्ण अन्यथा
		pr_warn("md-cluster: No good device id found to send\n");
	clear_bit(MD_CLUSTER_SEND_LOCKED_ALREADY, &cinfo->state);
	unlock_comm(cinfo);
	वापस ret;
पूर्ण

अटल व्योम metadata_update_cancel(काष्ठा mddev *mddev)
अणु
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;
	clear_bit(MD_CLUSTER_SEND_LOCKED_ALREADY, &cinfo->state);
	unlock_comm(cinfo);
पूर्ण

अटल पूर्णांक update_biपंचांगap_size(काष्ठा mddev *mddev, sector_t size)
अणु
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;
	काष्ठा cluster_msg cmsg = अणु0पूर्ण;
	पूर्णांक ret;

	cmsg.type = cpu_to_le32(BITMAP_RESIZE);
	cmsg.high = cpu_to_le64(size);
	ret = sendmsg(cinfo, &cmsg, 0);
	अगर (ret)
		pr_err("%s:%d: failed to send BITMAP_RESIZE message (%d)\n",
			__func__, __LINE__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक resize_biपंचांगaps(काष्ठा mddev *mddev, sector_t newsize, sector_t oldsize)
अणु
	काष्ठा biपंचांगap_counts *counts;
	अक्षर str[64];
	काष्ठा dlm_lock_resource *bm_lockres;
	काष्ठा biपंचांगap *biपंचांगap = mddev->biपंचांगap;
	अचिन्हित दीर्घ my_pages = biपंचांगap->counts.pages;
	पूर्णांक i, rv;

	/*
	 * We need to ensure all the nodes can grow to a larger
	 * biपंचांगap size beक्रमe make the reshaping.
	 */
	rv = update_biपंचांगap_size(mddev, newsize);
	अगर (rv)
		वापस rv;

	क्रम (i = 0; i < mddev->biपंचांगap_info.nodes; i++) अणु
		अगर (i == md_cluster_ops->slot_number(mddev))
			जारी;

		biपंचांगap = get_biपंचांगap_from_slot(mddev, i);
		अगर (IS_ERR(biपंचांगap)) अणु
			pr_err("can't get bitmap from slot %d\n", i);
			biपंचांगap = शून्य;
			जाओ out;
		पूर्ण
		counts = &biपंचांगap->counts;

		/*
		 * If we can hold the biपंचांगap lock of one node then
		 * the slot is not occupied, update the pages.
		 */
		snम_लिखो(str, 64, "bitmap%04d", i);
		bm_lockres = lockres_init(mddev, str, शून्य, 1);
		अगर (!bm_lockres) अणु
			pr_err("Cannot initialize %s lock\n", str);
			जाओ out;
		पूर्ण
		bm_lockres->flags |= DLM_LKF_NOQUEUE;
		rv = dlm_lock_sync(bm_lockres, DLM_LOCK_PW);
		अगर (!rv)
			counts->pages = my_pages;
		lockres_मुक्त(bm_lockres);

		अगर (my_pages != counts->pages)
			/*
			 * Let's revert the biपंचांगap size अगर one node
			 * can't resize biपंचांगap
			 */
			जाओ out;
		md_biपंचांगap_मुक्त(biपंचांगap);
	पूर्ण

	वापस 0;
out:
	md_biपंचांगap_मुक्त(biपंचांगap);
	update_biपंचांगap_size(mddev, oldsize);
	वापस -1;
पूर्ण

/*
 * वापस 0 अगर all the biपंचांगaps have the same sync_size
 */
अटल पूर्णांक cluster_check_sync_size(काष्ठा mddev *mddev)
अणु
	पूर्णांक i, rv;
	biपंचांगap_super_t *sb;
	अचिन्हित दीर्घ my_sync_size, sync_size = 0;
	पूर्णांक node_num = mddev->biपंचांगap_info.nodes;
	पूर्णांक current_slot = md_cluster_ops->slot_number(mddev);
	काष्ठा biपंचांगap *biपंचांगap = mddev->biपंचांगap;
	अक्षर str[64];
	काष्ठा dlm_lock_resource *bm_lockres;

	sb = kmap_atomic(biपंचांगap->storage.sb_page);
	my_sync_size = sb->sync_size;
	kunmap_atomic(sb);

	क्रम (i = 0; i < node_num; i++) अणु
		अगर (i == current_slot)
			जारी;

		biपंचांगap = get_biपंचांगap_from_slot(mddev, i);
		अगर (IS_ERR(biपंचांगap)) अणु
			pr_err("can't get bitmap from slot %d\n", i);
			वापस -1;
		पूर्ण

		/*
		 * If we can hold the biपंचांगap lock of one node then
		 * the slot is not occupied, update the sb.
		 */
		snम_लिखो(str, 64, "bitmap%04d", i);
		bm_lockres = lockres_init(mddev, str, शून्य, 1);
		अगर (!bm_lockres) अणु
			pr_err("md-cluster: Cannot initialize %s\n", str);
			md_biपंचांगap_मुक्त(biपंचांगap);
			वापस -1;
		पूर्ण
		bm_lockres->flags |= DLM_LKF_NOQUEUE;
		rv = dlm_lock_sync(bm_lockres, DLM_LOCK_PW);
		अगर (!rv)
			md_biपंचांगap_update_sb(biपंचांगap);
		lockres_मुक्त(bm_lockres);

		sb = kmap_atomic(biपंचांगap->storage.sb_page);
		अगर (sync_size == 0)
			sync_size = sb->sync_size;
		अन्यथा अगर (sync_size != sb->sync_size) अणु
			kunmap_atomic(sb);
			md_biपंचांगap_मुक्त(biपंचांगap);
			वापस -1;
		पूर्ण
		kunmap_atomic(sb);
		md_biपंचांगap_मुक्त(biपंचांगap);
	पूर्ण

	वापस (my_sync_size == sync_size) ? 0 : -1;
पूर्ण

/*
 * Update the size क्रम cluster raid is a little more complex, we perक्रमm it
 * by the steps:
 * 1. hold token lock and update superblock in initiator node.
 * 2. send METADATA_UPDATED msg to other nodes.
 * 3. The initiator node जारीs to check each biपंचांगap's sync_size, अगर all
 *    biपंचांगaps have the same value of sync_size, then we can set capacity and
 *    let other nodes to perक्रमm it. If one node can't update sync_size
 *    accordingly, we need to revert to previous value.
 */
अटल व्योम update_size(काष्ठा mddev *mddev, sector_t old_dev_sectors)
अणु
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;
	काष्ठा cluster_msg cmsg;
	काष्ठा md_rdev *rdev;
	पूर्णांक ret = 0;
	पूर्णांक raid_slot = -1;

	md_update_sb(mddev, 1);
	अगर (lock_comm(cinfo, 1)) अणु
		pr_err("%s: lock_comm failed\n", __func__);
		वापस;
	पूर्ण

	स_रखो(&cmsg, 0, माप(cmsg));
	cmsg.type = cpu_to_le32(METADATA_UPDATED);
	rdev_क्रम_each(rdev, mddev)
		अगर (rdev->raid_disk >= 0 && !test_bit(Faulty, &rdev->flags)) अणु
			raid_slot = rdev->desc_nr;
			अवरोध;
		पूर्ण
	अगर (raid_slot >= 0) अणु
		cmsg.raid_slot = cpu_to_le32(raid_slot);
		/*
		 * We can only change capiticy after all the nodes can करो it,
		 * so need to रुको after other nodes alपढ़ोy received the msg
		 * and handled the change
		 */
		ret = __sendmsg(cinfo, &cmsg);
		अगर (ret) अणु
			pr_err("%s:%d: failed to send METADATA_UPDATED msg\n",
			       __func__, __LINE__);
			unlock_comm(cinfo);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_err("md-cluster: No good device id found to send\n");
		unlock_comm(cinfo);
		वापस;
	पूर्ण

	/*
	 * check the sync_size from other node's biपंचांगap, अगर sync_size
	 * have alपढ़ोy updated in other nodes as expected, send an
	 * empty metadata msg to permit the change of capacity
	 */
	अगर (cluster_check_sync_size(mddev) == 0) अणु
		स_रखो(&cmsg, 0, माप(cmsg));
		cmsg.type = cpu_to_le32(CHANGE_CAPACITY);
		ret = __sendmsg(cinfo, &cmsg);
		अगर (ret)
			pr_err("%s:%d: failed to send CHANGE_CAPACITY msg\n",
			       __func__, __LINE__);
		set_capacity_and_notअगरy(mddev->gendisk, mddev->array_sectors);
	पूर्ण अन्यथा अणु
		/* revert to previous sectors */
		ret = mddev->pers->resize(mddev, old_dev_sectors);
		ret = __sendmsg(cinfo, &cmsg);
		अगर (ret)
			pr_err("%s:%d: failed to send METADATA_UPDATED msg\n",
			       __func__, __LINE__);
	पूर्ण
	unlock_comm(cinfo);
पूर्ण

अटल पूर्णांक resync_start(काष्ठा mddev *mddev)
अणु
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;
	वापस dlm_lock_sync_पूर्णांकerruptible(cinfo->resync_lockres, DLM_LOCK_EX, mddev);
पूर्ण

अटल व्योम resync_info_get(काष्ठा mddev *mddev, sector_t *lo, sector_t *hi)
अणु
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;

	spin_lock_irq(&cinfo->suspend_lock);
	*lo = cinfo->suspend_lo;
	*hi = cinfo->suspend_hi;
	spin_unlock_irq(&cinfo->suspend_lock);
पूर्ण

अटल पूर्णांक resync_info_update(काष्ठा mddev *mddev, sector_t lo, sector_t hi)
अणु
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;
	काष्ठा resync_info ri;
	काष्ठा cluster_msg cmsg = अणु0पूर्ण;

	/* करो not send zero again, अगर we have sent beक्रमe */
	अगर (hi == 0) अणु
		स_नकल(&ri, cinfo->biपंचांगap_lockres->lksb.sb_lvbptr, माप(काष्ठा resync_info));
		अगर (le64_to_cpu(ri.hi) == 0)
			वापस 0;
	पूर्ण

	add_resync_info(cinfo->biपंचांगap_lockres, lo, hi);
	/* Re-acquire the lock to refresh LVB */
	dlm_lock_sync(cinfo->biपंचांगap_lockres, DLM_LOCK_PW);
	cmsg.type = cpu_to_le32(RESYNCING);
	cmsg.low = cpu_to_le64(lo);
	cmsg.high = cpu_to_le64(hi);

	/*
	 * mddev_lock is held अगर resync_info_update is called from
	 * resync_finish (md_reap_sync_thपढ़ो -> resync_finish)
	 */
	अगर (lo == 0 && hi == 0)
		वापस sendmsg(cinfo, &cmsg, 1);
	अन्यथा
		वापस sendmsg(cinfo, &cmsg, 0);
पूर्ण

अटल पूर्णांक resync_finish(काष्ठा mddev *mddev)
अणु
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;
	पूर्णांक ret = 0;

	clear_bit(MD_RESYNCING_REMOTE, &mddev->recovery);

	/*
	 * If resync thपढ़ो is पूर्णांकerrupted so we can't say resync is finished,
	 * another node will launch resync thपढ़ो to जारी.
	 */
	अगर (!test_bit(MD_CLOSING, &mddev->flags))
		ret = resync_info_update(mddev, 0, 0);
	dlm_unlock_sync(cinfo->resync_lockres);
	वापस ret;
पूर्ण

अटल पूर्णांक area_resyncing(काष्ठा mddev *mddev, पूर्णांक direction,
		sector_t lo, sector_t hi)
अणु
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;
	पूर्णांक ret = 0;

	अगर ((direction == READ) &&
		test_bit(MD_CLUSTER_SUSPEND_READ_BALANCING, &cinfo->state))
		वापस 1;

	spin_lock_irq(&cinfo->suspend_lock);
	अगर (hi > cinfo->suspend_lo && lo < cinfo->suspend_hi)
		ret = 1;
	spin_unlock_irq(&cinfo->suspend_lock);
	वापस ret;
पूर्ण

/* add_new_disk() - initiates a disk add
 * However, अगर this fails beक्रमe writing md_update_sb(),
 * add_new_disk_cancel() must be called to release token lock
 */
अटल पूर्णांक add_new_disk(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;
	काष्ठा cluster_msg cmsg;
	पूर्णांक ret = 0;
	काष्ठा mdp_superblock_1 *sb = page_address(rdev->sb_page);
	अक्षर *uuid = sb->device_uuid;

	स_रखो(&cmsg, 0, माप(cmsg));
	cmsg.type = cpu_to_le32(NEWDISK);
	स_नकल(cmsg.uuid, uuid, 16);
	cmsg.raid_slot = cpu_to_le32(rdev->desc_nr);
	अगर (lock_comm(cinfo, 1))
		वापस -EAGAIN;
	ret = __sendmsg(cinfo, &cmsg);
	अगर (ret) अणु
		unlock_comm(cinfo);
		वापस ret;
	पूर्ण
	cinfo->no_new_dev_lockres->flags |= DLM_LKF_NOQUEUE;
	ret = dlm_lock_sync(cinfo->no_new_dev_lockres, DLM_LOCK_EX);
	cinfo->no_new_dev_lockres->flags &= ~DLM_LKF_NOQUEUE;
	/* Some node करोes not "see" the device */
	अगर (ret == -EAGAIN)
		ret = -ENOENT;
	अगर (ret)
		unlock_comm(cinfo);
	अन्यथा अणु
		dlm_lock_sync(cinfo->no_new_dev_lockres, DLM_LOCK_CR);
		/* Since MD_CHANGE_DEVS will be set in add_bound_rdev which
		 * will run soon after add_new_disk, the below path will be
		 * invoked:
		 *   md_wakeup_thपढ़ो(mddev->thपढ़ो)
		 *	-> conf->thपढ़ो (raid1d)
		 *	-> md_check_recovery -> md_update_sb
		 *	-> metadata_update_start/finish
		 * MD_CLUSTER_SEND_LOCKED_ALREADY will be cleared eventually.
		 *
		 * For other failure हालs, metadata_update_cancel and
		 * add_new_disk_cancel also clear below bit as well.
		 * */
		set_bit(MD_CLUSTER_SEND_LOCKED_ALREADY, &cinfo->state);
		wake_up(&cinfo->रुको);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम add_new_disk_cancel(काष्ठा mddev *mddev)
अणु
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;
	clear_bit(MD_CLUSTER_SEND_LOCKED_ALREADY, &cinfo->state);
	unlock_comm(cinfo);
पूर्ण

अटल पूर्णांक new_disk_ack(काष्ठा mddev *mddev, bool ack)
अणु
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;

	अगर (!test_bit(MD_CLUSTER_WAITING_FOR_NEWDISK, &cinfo->state)) अणु
		pr_warn("md-cluster(%s): Spurious cluster confirmation\n", mdname(mddev));
		वापस -EINVAL;
	पूर्ण

	अगर (ack)
		dlm_unlock_sync(cinfo->no_new_dev_lockres);
	complete(&cinfo->newdisk_completion);
	वापस 0;
पूर्ण

अटल पूर्णांक हटाओ_disk(काष्ठा mddev *mddev, काष्ठा md_rdev *rdev)
अणु
	काष्ठा cluster_msg cmsg = अणु0पूर्ण;
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;
	cmsg.type = cpu_to_le32(REMOVE);
	cmsg.raid_slot = cpu_to_le32(rdev->desc_nr);
	वापस sendmsg(cinfo, &cmsg, 1);
पूर्ण

अटल पूर्णांक lock_all_biपंचांगaps(काष्ठा mddev *mddev)
अणु
	पूर्णांक slot, my_slot, ret, held = 1, i = 0;
	अक्षर str[64];
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;

	cinfo->other_biपंचांगap_lockres =
		kसुस्मृति(mddev->biपंचांगap_info.nodes - 1,
			माप(काष्ठा dlm_lock_resource *), GFP_KERNEL);
	अगर (!cinfo->other_biपंचांगap_lockres) अणु
		pr_err("md: can't alloc mem for other bitmap locks\n");
		वापस 0;
	पूर्ण

	my_slot = slot_number(mddev);
	क्रम (slot = 0; slot < mddev->biपंचांगap_info.nodes; slot++) अणु
		अगर (slot == my_slot)
			जारी;

		स_रखो(str, '\0', 64);
		snम_लिखो(str, 64, "bitmap%04d", slot);
		cinfo->other_biपंचांगap_lockres[i] = lockres_init(mddev, str, शून्य, 1);
		अगर (!cinfo->other_biपंचांगap_lockres[i])
			वापस -ENOMEM;

		cinfo->other_biपंचांगap_lockres[i]->flags |= DLM_LKF_NOQUEUE;
		ret = dlm_lock_sync(cinfo->other_biपंचांगap_lockres[i], DLM_LOCK_PW);
		अगर (ret)
			held = -1;
		i++;
	पूर्ण

	वापस held;
पूर्ण

अटल व्योम unlock_all_biपंचांगaps(काष्ठा mddev *mddev)
अणु
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;
	पूर्णांक i;

	/* release other node's biपंचांगap lock अगर they are existed */
	अगर (cinfo->other_biपंचांगap_lockres) अणु
		क्रम (i = 0; i < mddev->biपंचांगap_info.nodes - 1; i++) अणु
			अगर (cinfo->other_biपंचांगap_lockres[i]) अणु
				lockres_मुक्त(cinfo->other_biपंचांगap_lockres[i]);
			पूर्ण
		पूर्ण
		kमुक्त(cinfo->other_biपंचांगap_lockres);
		cinfo->other_biपंचांगap_lockres = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक gather_biपंचांगaps(काष्ठा md_rdev *rdev)
अणु
	पूर्णांक sn, err;
	sector_t lo, hi;
	काष्ठा cluster_msg cmsg = अणु0पूर्ण;
	काष्ठा mddev *mddev = rdev->mddev;
	काष्ठा md_cluster_info *cinfo = mddev->cluster_info;

	cmsg.type = cpu_to_le32(RE_ADD);
	cmsg.raid_slot = cpu_to_le32(rdev->desc_nr);
	err = sendmsg(cinfo, &cmsg, 1);
	अगर (err)
		जाओ out;

	क्रम (sn = 0; sn < mddev->biपंचांगap_info.nodes; sn++) अणु
		अगर (sn == (cinfo->slot_number - 1))
			जारी;
		err = md_biपंचांगap_copy_from_slot(mddev, sn, &lo, &hi, false);
		अगर (err) अणु
			pr_warn("md-cluster: Could not gather bitmaps from slot %d", sn);
			जाओ out;
		पूर्ण
		अगर ((hi > 0) && (lo < mddev->recovery_cp))
			mddev->recovery_cp = lo;
	पूर्ण
out:
	वापस err;
पूर्ण

अटल काष्ठा md_cluster_operations cluster_ops = अणु
	.join   = join,
	.leave  = leave,
	.slot_number = slot_number,
	.resync_start = resync_start,
	.resync_finish = resync_finish,
	.resync_info_update = resync_info_update,
	.resync_info_get = resync_info_get,
	.metadata_update_start = metadata_update_start,
	.metadata_update_finish = metadata_update_finish,
	.metadata_update_cancel = metadata_update_cancel,
	.area_resyncing = area_resyncing,
	.add_new_disk = add_new_disk,
	.add_new_disk_cancel = add_new_disk_cancel,
	.new_disk_ack = new_disk_ack,
	.हटाओ_disk = हटाओ_disk,
	.load_biपंचांगaps = load_biपंचांगaps,
	.gather_biपंचांगaps = gather_biपंचांगaps,
	.resize_biपंचांगaps = resize_biपंचांगaps,
	.lock_all_biपंचांगaps = lock_all_biपंचांगaps,
	.unlock_all_biपंचांगaps = unlock_all_biपंचांगaps,
	.update_size = update_size,
पूर्ण;

अटल पूर्णांक __init cluster_init(व्योम)
अणु
	pr_warn("md-cluster: support raid1 and raid10 (limited support)\n");
	pr_info("Registering Cluster MD functions\n");
	रेजिस्टर_md_cluster_operations(&cluster_ops, THIS_MODULE);
	वापस 0;
पूर्ण

अटल व्योम cluster_निकास(व्योम)
अणु
	unरेजिस्टर_md_cluster_operations();
पूर्ण

module_init(cluster_init);
module_निकास(cluster_निकास);
MODULE_AUTHOR("SUSE");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Clustering support for MD");
