<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2004, 2005 Oracle.  All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/file.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/configfs.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/crc32.h>
#समावेश <linux/समय.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/kसमय.स>
#समावेश "heartbeat.h"
#समावेश "tcp.h"
#समावेश "nodemanager.h"
#समावेश "quorum.h"

#समावेश "masklog.h"


/*
 * The first heartbeat pass had one global thपढ़ो that would serialize all hb
 * callback calls.  This global serializing sem should only be हटाओd once
 * we've made sure that all callees can deal with being called concurrently
 * from multiple hb region thपढ़ोs.
 */
अटल DECLARE_RWSEM(o2hb_callback_sem);

/*
 * multiple hb thपढ़ोs are watching multiple regions.  A node is live
 * whenever any of the thपढ़ोs sees activity from the node in its region.
 */
अटल DEFINE_SPINLOCK(o2hb_live_lock);
अटल काष्ठा list_head o2hb_live_slots[O2NM_MAX_NODES];
अटल अचिन्हित दीर्घ o2hb_live_node_biपंचांगap[BITS_TO_LONGS(O2NM_MAX_NODES)];
अटल LIST_HEAD(o2hb_node_events);
अटल DECLARE_WAIT_QUEUE_HEAD(o2hb_steady_queue);

/*
 * In global heartbeat, we मुख्यtain a series of region biपंचांगaps.
 * 	- o2hb_region_biपंचांगap allows us to limit the region number to max region.
 * 	- o2hb_live_region_biपंचांगap tracks live regions (seen steady iterations).
 * 	- o2hb_quorum_region_biपंचांगap tracks live regions that have seen all nodes
 * 		heartbeat on it.
 * 	- o2hb_failed_region_biपंचांगap tracks the regions that have seen io समयouts.
 */
अटल अचिन्हित दीर्घ o2hb_region_biपंचांगap[BITS_TO_LONGS(O2NM_MAX_REGIONS)];
अटल अचिन्हित दीर्घ o2hb_live_region_biपंचांगap[BITS_TO_LONGS(O2NM_MAX_REGIONS)];
अटल अचिन्हित दीर्घ o2hb_quorum_region_biपंचांगap[BITS_TO_LONGS(O2NM_MAX_REGIONS)];
अटल अचिन्हित दीर्घ o2hb_failed_region_biपंचांगap[BITS_TO_LONGS(O2NM_MAX_REGIONS)];

#घोषणा O2HB_DB_TYPE_LIVENODES		0
#घोषणा O2HB_DB_TYPE_LIVEREGIONS	1
#घोषणा O2HB_DB_TYPE_QUORUMREGIONS	2
#घोषणा O2HB_DB_TYPE_FAILEDREGIONS	3
#घोषणा O2HB_DB_TYPE_REGION_LIVENODES	4
#घोषणा O2HB_DB_TYPE_REGION_NUMBER	5
#घोषणा O2HB_DB_TYPE_REGION_ELAPSED_TIME	6
#घोषणा O2HB_DB_TYPE_REGION_PINNED	7
काष्ठा o2hb_debug_buf अणु
	पूर्णांक db_type;
	पूर्णांक db_size;
	पूर्णांक db_len;
	व्योम *db_data;
पूर्ण;

अटल काष्ठा o2hb_debug_buf *o2hb_db_livenodes;
अटल काष्ठा o2hb_debug_buf *o2hb_db_liveregions;
अटल काष्ठा o2hb_debug_buf *o2hb_db_quorumregions;
अटल काष्ठा o2hb_debug_buf *o2hb_db_failedregions;

#घोषणा O2HB_DEBUG_सूची			"o2hb"
#घोषणा O2HB_DEBUG_LIVENODES		"livenodes"
#घोषणा O2HB_DEBUG_LIVEREGIONS		"live_regions"
#घोषणा O2HB_DEBUG_QUORUMREGIONS	"quorum_regions"
#घोषणा O2HB_DEBUG_FAILEDREGIONS	"failed_regions"
#घोषणा O2HB_DEBUG_REGION_NUMBER	"num"
#घोषणा O2HB_DEBUG_REGION_ELAPSED_TIME	"elapsed_time_in_ms"
#घोषणा O2HB_DEBUG_REGION_PINNED	"pinned"

अटल काष्ठा dentry *o2hb_debug_dir;

अटल LIST_HEAD(o2hb_all_regions);

अटल काष्ठा o2hb_callback अणु
	काष्ठा list_head list;
पूर्ण o2hb_callbacks[O2HB_NUM_CB];

अटल काष्ठा o2hb_callback *hbcall_from_type(क्रमागत o2hb_callback_type type);

क्रमागत o2hb_heartbeat_modes अणु
	O2HB_HEARTBEAT_LOCAL		= 0,
	O2HB_HEARTBEAT_GLOBAL,
	O2HB_HEARTBEAT_NUM_MODES,
पूर्ण;

अटल स्थिर अक्षर *o2hb_heartbeat_mode_desc[O2HB_HEARTBEAT_NUM_MODES] = अणु
	"local",	/* O2HB_HEARTBEAT_LOCAL */
	"global",	/* O2HB_HEARTBEAT_GLOBAL */
पूर्ण;

अचिन्हित पूर्णांक o2hb_dead_threshold = O2HB_DEFAULT_DEAD_THRESHOLD;
अटल अचिन्हित पूर्णांक o2hb_heartbeat_mode = O2HB_HEARTBEAT_LOCAL;

/*
 * o2hb_dependent_users tracks the number of रेजिस्टरed callbacks that depend
 * on heartbeat. o2net and o2dlm are two entities that रेजिस्टर this callback.
 * However only o2dlm depends on the heartbeat. It करोes not want the heartbeat
 * to stop जबतक a dlm करोमुख्य is still active.
 */
अटल अचिन्हित पूर्णांक o2hb_dependent_users;

/*
 * In global heartbeat mode, all regions are pinned अगर there are one or more
 * dependent users and the quorum region count is <= O2HB_PIN_CUT_OFF. All
 * regions are unpinned अगर the region count exceeds the cut off or the number
 * of dependent users falls to zero.
 */
#घोषणा O2HB_PIN_CUT_OFF		3

/*
 * In local heartbeat mode, we assume the dlm करोमुख्य name to be the same as
 * region uuid. This is true क्रम करोमुख्यs created क्रम the file प्रणाली but not
 * necessarily true क्रम userdlm करोमुख्यs. This is a known limitation.
 *
 * In global heartbeat mode, we pin/unpin all o2hb regions. This solution
 * works क्रम both file प्रणाली and userdlm करोमुख्यs.
 */
अटल पूर्णांक o2hb_region_pin(स्थिर अक्षर *region_uuid);
अटल व्योम o2hb_region_unpin(स्थिर अक्षर *region_uuid);

/* Only sets a new threshold अगर there are no active regions.
 *
 * No locking or otherwise पूर्णांकeresting code is required क्रम पढ़ोing
 * o2hb_dead_threshold as it can't change once regions are active and
 * it's not पूर्णांकeresting to anyone until then anyway. */
अटल व्योम o2hb_dead_threshold_set(अचिन्हित पूर्णांक threshold)
अणु
	अगर (threshold > O2HB_MIN_DEAD_THRESHOLD) अणु
		spin_lock(&o2hb_live_lock);
		अगर (list_empty(&o2hb_all_regions))
			o2hb_dead_threshold = threshold;
		spin_unlock(&o2hb_live_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक o2hb_global_heartbeat_mode_set(अचिन्हित पूर्णांक hb_mode)
अणु
	पूर्णांक ret = -1;

	अगर (hb_mode < O2HB_HEARTBEAT_NUM_MODES) अणु
		spin_lock(&o2hb_live_lock);
		अगर (list_empty(&o2hb_all_regions)) अणु
			o2hb_heartbeat_mode = hb_mode;
			ret = 0;
		पूर्ण
		spin_unlock(&o2hb_live_lock);
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा o2hb_node_event अणु
	काष्ठा list_head        hn_item;
	क्रमागत o2hb_callback_type hn_event_type;
	काष्ठा o2nm_node        *hn_node;
	पूर्णांक                     hn_node_num;
पूर्ण;

काष्ठा o2hb_disk_slot अणु
	काष्ठा o2hb_disk_heartbeat_block *ds_raw_block;
	u8			ds_node_num;
	u64			ds_last_समय;
	u64			ds_last_generation;
	u16			ds_equal_samples;
	u16			ds_changed_samples;
	काष्ठा list_head	ds_live_item;
पूर्ण;

/* each thपढ़ो owns a region.. when we're asked to tear करोwn the region
 * we ask the thपढ़ो to stop, who cleans up the region */
काष्ठा o2hb_region अणु
	काष्ठा config_item	hr_item;

	काष्ठा list_head	hr_all_item;
	अचिन्हित		hr_unclean_stop:1,
				hr_पातed_start:1,
				hr_item_pinned:1,
				hr_item_dropped:1,
				hr_node_deleted:1;

	/* रक्षित by the hr_callback_sem */
	काष्ठा task_काष्ठा 	*hr_task;

	अचिन्हित पूर्णांक		hr_blocks;
	अचिन्हित दीर्घ दीर्घ	hr_start_block;

	अचिन्हित पूर्णांक		hr_block_bits;
	अचिन्हित पूर्णांक		hr_block_bytes;

	अचिन्हित पूर्णांक		hr_slots_per_page;
	अचिन्हित पूर्णांक		hr_num_pages;

	काष्ठा page             **hr_slot_data;
	काष्ठा block_device	*hr_bdev;
	काष्ठा o2hb_disk_slot	*hr_slots;

	/* live node map of this region */
	अचिन्हित दीर्घ		hr_live_node_biपंचांगap[BITS_TO_LONGS(O2NM_MAX_NODES)];
	अचिन्हित पूर्णांक		hr_region_num;

	काष्ठा dentry		*hr_debug_dir;
	काष्ठा o2hb_debug_buf	*hr_db_livenodes;
	काष्ठा o2hb_debug_buf	*hr_db_regnum;
	काष्ठा o2hb_debug_buf	*hr_db_elapsed_समय;
	काष्ठा o2hb_debug_buf	*hr_db_pinned;

	/* let the person setting up hb रुको क्रम it to वापस until it
	 * has reached a 'steady' state.  This will be fixed when we have
	 * a more complete api that करोesn't lead to this sort of fragility. */
	atomic_t		hr_steady_iterations;

	/* terminate o2hb thपढ़ो अगर it करोes not reach steady state
	 * (hr_steady_iterations == 0) within hr_unsteady_iterations */
	atomic_t		hr_unsteady_iterations;

	अक्षर			hr_dev_name[BDEVNAME_SIZE];

	अचिन्हित पूर्णांक		hr_समयout_ms;

	/* अक्रमomized as the region goes up and करोwn so that a node
	 * recognizes a node going up and करोwn in one iteration */
	u64			hr_generation;

	काष्ठा delayed_work	hr_ग_लिखो_समयout_work;
	अचिन्हित दीर्घ		hr_last_समयout_start;

	/* negotiate समयr, used to negotiate extending hb समयout. */
	काष्ठा delayed_work	hr_nego_समयout_work;
	अचिन्हित दीर्घ		hr_nego_node_biपंचांगap[BITS_TO_LONGS(O2NM_MAX_NODES)];

	/* Used during o2hb_check_slot to hold a copy of the block
	 * being checked because we temporarily have to zero out the
	 * crc field. */
	काष्ठा o2hb_disk_heartbeat_block *hr_पंचांगp_block;

	/* Message key क्रम negotiate समयout message. */
	अचिन्हित पूर्णांक		hr_key;
	काष्ठा list_head	hr_handler_list;

	/* last hb status, 0 क्रम success, other value क्रम error. */
	पूर्णांक			hr_last_hb_status;
पूर्ण;

काष्ठा o2hb_bio_रुको_ctxt अणु
	atomic_t          wc_num_reqs;
	काष्ठा completion wc_io_complete;
	पूर्णांक               wc_error;
पूर्ण;

#घोषणा O2HB_NEGO_TIMEOUT_MS (O2HB_MAX_WRITE_TIMEOUT_MS/2)

क्रमागत अणु
	O2HB_NEGO_TIMEOUT_MSG = 1,
	O2HB_NEGO_APPROVE_MSG = 2,
पूर्ण;

काष्ठा o2hb_nego_msg अणु
	u8 node_num;
पूर्ण;

अटल व्योम o2hb_ग_लिखो_समयout(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक failed, quorum;
	काष्ठा o2hb_region *reg =
		container_of(work, काष्ठा o2hb_region,
			     hr_ग_लिखो_समयout_work.work);

	mlog(ML_ERROR, "Heartbeat write timeout to device %s after %u "
	     "milliseconds\n", reg->hr_dev_name,
	     jअगरfies_to_msecs(jअगरfies - reg->hr_last_समयout_start));

	अगर (o2hb_global_heartbeat_active()) अणु
		spin_lock(&o2hb_live_lock);
		अगर (test_bit(reg->hr_region_num, o2hb_quorum_region_biपंचांगap))
			set_bit(reg->hr_region_num, o2hb_failed_region_biपंचांगap);
		failed = biपंचांगap_weight(o2hb_failed_region_biपंचांगap,
					O2NM_MAX_REGIONS);
		quorum = biपंचांगap_weight(o2hb_quorum_region_biपंचांगap,
					O2NM_MAX_REGIONS);
		spin_unlock(&o2hb_live_lock);

		mlog(ML_HEARTBEAT, "Number of regions %d, failed regions %d\n",
		     quorum, failed);

		/*
		 * Fence अगर the number of failed regions >= half the number
		 * of  quorum regions
		 */
		अगर ((failed << 1) < quorum)
			वापस;
	पूर्ण

	o2quo_disk_समयout();
पूर्ण

अटल व्योम o2hb_arm_समयout(काष्ठा o2hb_region *reg)
अणु
	/* Arm ग_लिखोout only after thपढ़ो reaches steady state */
	अगर (atomic_पढ़ो(&reg->hr_steady_iterations) != 0)
		वापस;

	mlog(ML_HEARTBEAT, "Queue write timeout for %u ms\n",
	     O2HB_MAX_WRITE_TIMEOUT_MS);

	अगर (o2hb_global_heartbeat_active()) अणु
		spin_lock(&o2hb_live_lock);
		clear_bit(reg->hr_region_num, o2hb_failed_region_biपंचांगap);
		spin_unlock(&o2hb_live_lock);
	पूर्ण
	cancel_delayed_work(&reg->hr_ग_लिखो_समयout_work);
	schedule_delayed_work(&reg->hr_ग_लिखो_समयout_work,
			      msecs_to_jअगरfies(O2HB_MAX_WRITE_TIMEOUT_MS));

	cancel_delayed_work(&reg->hr_nego_समयout_work);
	/* negotiate समयout must be less than ग_लिखो समयout. */
	schedule_delayed_work(&reg->hr_nego_समयout_work,
			      msecs_to_jअगरfies(O2HB_NEGO_TIMEOUT_MS));
	स_रखो(reg->hr_nego_node_biपंचांगap, 0, माप(reg->hr_nego_node_biपंचांगap));
पूर्ण

अटल व्योम o2hb_disarm_समयout(काष्ठा o2hb_region *reg)
अणु
	cancel_delayed_work_sync(&reg->hr_ग_लिखो_समयout_work);
	cancel_delayed_work_sync(&reg->hr_nego_समयout_work);
पूर्ण

अटल पूर्णांक o2hb_send_nego_msg(पूर्णांक key, पूर्णांक type, u8 target)
अणु
	काष्ठा o2hb_nego_msg msg;
	पूर्णांक status, ret;

	msg.node_num = o2nm_this_node();
again:
	ret = o2net_send_message(type, key, &msg, माप(msg),
			target, &status);

	अगर (ret == -EAGAIN || ret == -ENOMEM) अणु
		msleep(100);
		जाओ again;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम o2hb_nego_समयout(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ live_node_biपंचांगap[BITS_TO_LONGS(O2NM_MAX_NODES)];
	पूर्णांक master_node, i, ret;
	काष्ठा o2hb_region *reg;

	reg = container_of(work, काष्ठा o2hb_region, hr_nego_समयout_work.work);
	/* करोn't negotiate समयout अगर last hb failed since it is very
	 * possible io failed. Should let ग_लिखो समयout fence self.
	 */
	अगर (reg->hr_last_hb_status)
		वापस;

	o2hb_fill_node_map(live_node_biपंचांगap, माप(live_node_biपंचांगap));
	/* lowest node as master node to make negotiate decision. */
	master_node = find_next_bit(live_node_biपंचांगap, O2NM_MAX_NODES, 0);

	अगर (master_node == o2nm_this_node()) अणु
		अगर (!test_bit(master_node, reg->hr_nego_node_biपंचांगap)) अणु
			prपूर्णांकk(KERN_NOTICE "o2hb: node %d hb write hung for %ds on region %s (%s).\n",
				o2nm_this_node(), O2HB_NEGO_TIMEOUT_MS/1000,
				config_item_name(&reg->hr_item), reg->hr_dev_name);
			set_bit(master_node, reg->hr_nego_node_biपंचांगap);
		पूर्ण
		अगर (स_भेद(reg->hr_nego_node_biपंचांगap, live_node_biपंचांगap,
				माप(reg->hr_nego_node_biपंचांगap))) अणु
			/* check negotiate biपंचांगap every second to करो समयout
			 * approve decision.
			 */
			schedule_delayed_work(&reg->hr_nego_समयout_work,
				msecs_to_jअगरfies(1000));

			वापस;
		पूर्ण

		prपूर्णांकk(KERN_NOTICE "o2hb: all nodes hb write hung, maybe region %s (%s) is down.\n",
			config_item_name(&reg->hr_item), reg->hr_dev_name);
		/* approve negotiate समयout request. */
		o2hb_arm_समयout(reg);

		i = -1;
		जबतक ((i = find_next_bit(live_node_biपंचांगap,
				O2NM_MAX_NODES, i + 1)) < O2NM_MAX_NODES) अणु
			अगर (i == master_node)
				जारी;

			mlog(ML_HEARTBEAT, "send NEGO_APPROVE msg to node %d\n", i);
			ret = o2hb_send_nego_msg(reg->hr_key,
					O2HB_NEGO_APPROVE_MSG, i);
			अगर (ret)
				mlog(ML_ERROR, "send NEGO_APPROVE msg to node %d fail %d\n",
					i, ret);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* negotiate समयout with master node. */
		prपूर्णांकk(KERN_NOTICE "o2hb: node %d hb write hung for %ds on region %s (%s), negotiate timeout with node %d.\n",
			o2nm_this_node(), O2HB_NEGO_TIMEOUT_MS/1000, config_item_name(&reg->hr_item),
			reg->hr_dev_name, master_node);
		ret = o2hb_send_nego_msg(reg->hr_key, O2HB_NEGO_TIMEOUT_MSG,
				master_node);
		अगर (ret)
			mlog(ML_ERROR, "send NEGO_TIMEOUT msg to node %d fail %d\n",
				master_node, ret);
	पूर्ण
पूर्ण

अटल पूर्णांक o2hb_nego_समयout_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
				व्योम **ret_data)
अणु
	काष्ठा o2hb_region *reg = data;
	काष्ठा o2hb_nego_msg *nego_msg;

	nego_msg = (काष्ठा o2hb_nego_msg *)msg->buf;
	prपूर्णांकk(KERN_NOTICE "o2hb: receive negotiate timeout message from node %d on region %s (%s).\n",
		nego_msg->node_num, config_item_name(&reg->hr_item), reg->hr_dev_name);
	अगर (nego_msg->node_num < O2NM_MAX_NODES)
		set_bit(nego_msg->node_num, reg->hr_nego_node_biपंचांगap);
	अन्यथा
		mlog(ML_ERROR, "got nego timeout message from bad node.\n");

	वापस 0;
पूर्ण

अटल पूर्णांक o2hb_nego_approve_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
				व्योम **ret_data)
अणु
	काष्ठा o2hb_region *reg = data;

	prपूर्णांकk(KERN_NOTICE "o2hb: negotiate timeout approved by master node on region %s (%s).\n",
		config_item_name(&reg->hr_item), reg->hr_dev_name);
	o2hb_arm_समयout(reg);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम o2hb_bio_रुको_init(काष्ठा o2hb_bio_रुको_ctxt *wc)
अणु
	atomic_set(&wc->wc_num_reqs, 1);
	init_completion(&wc->wc_io_complete);
	wc->wc_error = 0;
पूर्ण

/* Used in error paths too */
अटल अंतरभूत व्योम o2hb_bio_रुको_dec(काष्ठा o2hb_bio_रुको_ctxt *wc,
				     अचिन्हित पूर्णांक num)
अणु
	/* sadly atomic_sub_and_test() isn't available on all platक्रमms.  The
	 * good news is that the fast path only completes one at a समय */
	जबतक(num--) अणु
		अगर (atomic_dec_and_test(&wc->wc_num_reqs)) अणु
			BUG_ON(num > 0);
			complete(&wc->wc_io_complete);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम o2hb_रुको_on_io(काष्ठा o2hb_bio_रुको_ctxt *wc)
अणु
	o2hb_bio_रुको_dec(wc, 1);
	रुको_क्रम_completion(&wc->wc_io_complete);
पूर्ण

अटल व्योम o2hb_bio_end_io(काष्ठा bio *bio)
अणु
	काष्ठा o2hb_bio_रुको_ctxt *wc = bio->bi_निजी;

	अगर (bio->bi_status) अणु
		mlog(ML_ERROR, "IO Error %d\n", bio->bi_status);
		wc->wc_error = blk_status_to_त्रुटि_सं(bio->bi_status);
	पूर्ण

	o2hb_bio_रुको_dec(wc, 1);
	bio_put(bio);
पूर्ण

/* Setup a Bio to cover I/O against num_slots slots starting at
 * start_slot. */
अटल काष्ठा bio *o2hb_setup_one_bio(काष्ठा o2hb_region *reg,
				      काष्ठा o2hb_bio_रुको_ctxt *wc,
				      अचिन्हित पूर्णांक *current_slot,
				      अचिन्हित पूर्णांक max_slots, पूर्णांक op,
				      पूर्णांक op_flags)
अणु
	पूर्णांक len, current_page;
	अचिन्हित पूर्णांक vec_len, vec_start;
	अचिन्हित पूर्णांक bits = reg->hr_block_bits;
	अचिन्हित पूर्णांक spp = reg->hr_slots_per_page;
	अचिन्हित पूर्णांक cs = *current_slot;
	काष्ठा bio *bio;
	काष्ठा page *page;

	/* Testing has shown this allocation to take दीर्घ enough under
	 * GFP_KERNEL that the local node can get fenced. It would be
	 * nicest अगर we could pre-allocate these bios and aव्योम this
	 * all together. */
	bio = bio_alloc(GFP_ATOMIC, 16);
	अगर (!bio) अणु
		mlog(ML_ERROR, "Could not alloc slots BIO!\n");
		bio = ERR_PTR(-ENOMEM);
		जाओ bail;
	पूर्ण

	/* Must put everything in 512 byte sectors क्रम the bio... */
	bio->bi_iter.bi_sector = (reg->hr_start_block + cs) << (bits - 9);
	bio_set_dev(bio, reg->hr_bdev);
	bio->bi_निजी = wc;
	bio->bi_end_io = o2hb_bio_end_io;
	bio_set_op_attrs(bio, op, op_flags);

	vec_start = (cs << bits) % PAGE_SIZE;
	जबतक(cs < max_slots) अणु
		current_page = cs / spp;
		page = reg->hr_slot_data[current_page];

		vec_len = min(PAGE_SIZE - vec_start,
			      (max_slots-cs) * (PAGE_SIZE/spp) );

		mlog(ML_HB_BIO, "page %d, vec_len = %u, vec_start = %u\n",
		     current_page, vec_len, vec_start);

		len = bio_add_page(bio, page, vec_len, vec_start);
		अगर (len != vec_len) अवरोध;

		cs += vec_len / (PAGE_SIZE/spp);
		vec_start = 0;
	पूर्ण

bail:
	*current_slot = cs;
	वापस bio;
पूर्ण

अटल पूर्णांक o2hb_पढ़ो_slots(काष्ठा o2hb_region *reg,
			   अचिन्हित पूर्णांक begin_slot,
			   अचिन्हित पूर्णांक max_slots)
अणु
	अचिन्हित पूर्णांक current_slot = begin_slot;
	पूर्णांक status;
	काष्ठा o2hb_bio_रुको_ctxt wc;
	काष्ठा bio *bio;

	o2hb_bio_रुको_init(&wc);

	जबतक(current_slot < max_slots) अणु
		bio = o2hb_setup_one_bio(reg, &wc, &current_slot, max_slots,
					 REQ_OP_READ, 0);
		अगर (IS_ERR(bio)) अणु
			status = PTR_ERR(bio);
			mlog_त्रुटि_सं(status);
			जाओ bail_and_रुको;
		पूर्ण

		atomic_inc(&wc.wc_num_reqs);
		submit_bio(bio);
	पूर्ण

	status = 0;

bail_and_रुको:
	o2hb_रुको_on_io(&wc);
	अगर (wc.wc_error && !status)
		status = wc.wc_error;

	वापस status;
पूर्ण

अटल पूर्णांक o2hb_issue_node_ग_लिखो(काष्ठा o2hb_region *reg,
				 काष्ठा o2hb_bio_रुको_ctxt *ग_लिखो_wc)
अणु
	पूर्णांक status;
	अचिन्हित पूर्णांक slot;
	काष्ठा bio *bio;

	o2hb_bio_रुको_init(ग_लिखो_wc);

	slot = o2nm_this_node();

	bio = o2hb_setup_one_bio(reg, ग_लिखो_wc, &slot, slot+1, REQ_OP_WRITE,
				 REQ_SYNC);
	अगर (IS_ERR(bio)) अणु
		status = PTR_ERR(bio);
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	atomic_inc(&ग_लिखो_wc->wc_num_reqs);
	submit_bio(bio);

	status = 0;
bail:
	वापस status;
पूर्ण

अटल u32 o2hb_compute_block_crc_le(काष्ठा o2hb_region *reg,
				     काष्ठा o2hb_disk_heartbeat_block *hb_block)
अणु
	__le32 old_cksum;
	u32 ret;

	/* We want to compute the block crc with a 0 value in the
	 * hb_cksum field. Save it off here and replace after the
	 * crc. */
	old_cksum = hb_block->hb_cksum;
	hb_block->hb_cksum = 0;

	ret = crc32_le(0, (अचिन्हित अक्षर *) hb_block, reg->hr_block_bytes);

	hb_block->hb_cksum = old_cksum;

	वापस ret;
पूर्ण

अटल व्योम o2hb_dump_slot(काष्ठा o2hb_disk_heartbeat_block *hb_block)
अणु
	mlog(ML_ERROR, "Dump slot information: seq = 0x%llx, node = %u, "
	     "cksum = 0x%x, generation 0x%llx\n",
	     (दीर्घ दीर्घ)le64_to_cpu(hb_block->hb_seq),
	     hb_block->hb_node, le32_to_cpu(hb_block->hb_cksum),
	     (दीर्घ दीर्घ)le64_to_cpu(hb_block->hb_generation));
पूर्ण

अटल पूर्णांक o2hb_verअगरy_crc(काष्ठा o2hb_region *reg,
			   काष्ठा o2hb_disk_heartbeat_block *hb_block)
अणु
	u32 पढ़ो, computed;

	पढ़ो = le32_to_cpu(hb_block->hb_cksum);
	computed = o2hb_compute_block_crc_le(reg, hb_block);

	वापस पढ़ो == computed;
पूर्ण

/*
 * Compare the slot data with what we wrote in the last iteration.
 * If the match fails, prपूर्णांक an appropriate error message. This is to
 * detect errors like... another node hearting on the same slot,
 * flaky device that is losing ग_लिखोs, etc.
 * Returns 1 अगर check succeeds, 0 otherwise.
 */
अटल पूर्णांक o2hb_check_own_slot(काष्ठा o2hb_region *reg)
अणु
	काष्ठा o2hb_disk_slot *slot;
	काष्ठा o2hb_disk_heartbeat_block *hb_block;
	अक्षर *errstr;

	slot = &reg->hr_slots[o2nm_this_node()];
	/* Don't check on our 1st बारtamp */
	अगर (!slot->ds_last_समय)
		वापस 0;

	hb_block = slot->ds_raw_block;
	अगर (le64_to_cpu(hb_block->hb_seq) == slot->ds_last_समय &&
	    le64_to_cpu(hb_block->hb_generation) == slot->ds_last_generation &&
	    hb_block->hb_node == slot->ds_node_num)
		वापस 1;

#घोषणा ERRSTR1		"Another node is heartbeating on device"
#घोषणा ERRSTR2		"Heartbeat generation mismatch on device"
#घोषणा ERRSTR3		"Heartbeat sequence mismatch on device"

	अगर (hb_block->hb_node != slot->ds_node_num)
		errstr = ERRSTR1;
	अन्यथा अगर (le64_to_cpu(hb_block->hb_generation) !=
		 slot->ds_last_generation)
		errstr = ERRSTR2;
	अन्यथा
		errstr = ERRSTR3;

	mlog(ML_ERROR, "%s (%s): expected(%u:0x%llx, 0x%llx), "
	     "ondisk(%u:0x%llx, 0x%llx)\n", errstr, reg->hr_dev_name,
	     slot->ds_node_num, (अचिन्हित दीर्घ दीर्घ)slot->ds_last_generation,
	     (अचिन्हित दीर्घ दीर्घ)slot->ds_last_समय, hb_block->hb_node,
	     (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(hb_block->hb_generation),
	     (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(hb_block->hb_seq));

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम o2hb_prepare_block(काष्ठा o2hb_region *reg,
				      u64 generation)
अणु
	पूर्णांक node_num;
	u64 cpuसमय;
	काष्ठा o2hb_disk_slot *slot;
	काष्ठा o2hb_disk_heartbeat_block *hb_block;

	node_num = o2nm_this_node();
	slot = &reg->hr_slots[node_num];

	hb_block = (काष्ठा o2hb_disk_heartbeat_block *)slot->ds_raw_block;
	स_रखो(hb_block, 0, reg->hr_block_bytes);
	/* TODO: समय stuff */
	cpuसमय = kसमय_get_real_seconds();
	अगर (!cpuसमय)
		cpuसमय = 1;

	hb_block->hb_seq = cpu_to_le64(cpuसमय);
	hb_block->hb_node = node_num;
	hb_block->hb_generation = cpu_to_le64(generation);
	hb_block->hb_dead_ms = cpu_to_le32(o2hb_dead_threshold * O2HB_REGION_TIMEOUT_MS);

	/* This step must always happen last! */
	hb_block->hb_cksum = cpu_to_le32(o2hb_compute_block_crc_le(reg,
								   hb_block));

	mlog(ML_HB_BIO, "our node generation = 0x%llx, cksum = 0x%x\n",
	     (दीर्घ दीर्घ)generation,
	     le32_to_cpu(hb_block->hb_cksum));
पूर्ण

अटल व्योम o2hb_fire_callbacks(काष्ठा o2hb_callback *hbcall,
				काष्ठा o2nm_node *node,
				पूर्णांक idx)
अणु
	काष्ठा o2hb_callback_func *f;

	list_क्रम_each_entry(f, &hbcall->list, hc_item) अणु
		mlog(ML_HEARTBEAT, "calling funcs %p\n", f);
		(f->hc_func)(node, idx, f->hc_data);
	पूर्ण
पूर्ण

/* Will run the list in order until we process the passed event */
अटल व्योम o2hb_run_event_list(काष्ठा o2hb_node_event *queued_event)
अणु
	काष्ठा o2hb_callback *hbcall;
	काष्ठा o2hb_node_event *event;

	/* Holding callback sem assures we करोn't alter the callback
	 * lists when करोing this, and serializes ourselves with other
	 * processes wanting callbacks. */
	करोwn_ग_लिखो(&o2hb_callback_sem);

	spin_lock(&o2hb_live_lock);
	जबतक (!list_empty(&o2hb_node_events)
	       && !list_empty(&queued_event->hn_item)) अणु
		event = list_entry(o2hb_node_events.next,
				   काष्ठा o2hb_node_event,
				   hn_item);
		list_del_init(&event->hn_item);
		spin_unlock(&o2hb_live_lock);

		mlog(ML_HEARTBEAT, "Node %s event for %d\n",
		     event->hn_event_type == O2HB_NODE_UP_CB ? "UP" : "DOWN",
		     event->hn_node_num);

		hbcall = hbcall_from_type(event->hn_event_type);

		/* We should *never* have gotten on to the list with a
		 * bad type... This isn't something that we should try
		 * to recover from. */
		BUG_ON(IS_ERR(hbcall));

		o2hb_fire_callbacks(hbcall, event->hn_node, event->hn_node_num);

		spin_lock(&o2hb_live_lock);
	पूर्ण
	spin_unlock(&o2hb_live_lock);

	up_ग_लिखो(&o2hb_callback_sem);
पूर्ण

अटल व्योम o2hb_queue_node_event(काष्ठा o2hb_node_event *event,
				  क्रमागत o2hb_callback_type type,
				  काष्ठा o2nm_node *node,
				  पूर्णांक node_num)
अणु
	निश्चित_spin_locked(&o2hb_live_lock);

	BUG_ON((!node) && (type != O2HB_NODE_DOWN_CB));

	event->hn_event_type = type;
	event->hn_node = node;
	event->hn_node_num = node_num;

	mlog(ML_HEARTBEAT, "Queue node %s event for node %d\n",
	     type == O2HB_NODE_UP_CB ? "UP" : "DOWN", node_num);

	list_add_tail(&event->hn_item, &o2hb_node_events);
पूर्ण

अटल व्योम o2hb_shutकरोwn_slot(काष्ठा o2hb_disk_slot *slot)
अणु
	काष्ठा o2hb_node_event event =
		अणु .hn_item = LIST_HEAD_INIT(event.hn_item), पूर्ण;
	काष्ठा o2nm_node *node;
	पूर्णांक queued = 0;

	node = o2nm_get_node_by_num(slot->ds_node_num);
	अगर (!node)
		वापस;

	spin_lock(&o2hb_live_lock);
	अगर (!list_empty(&slot->ds_live_item)) अणु
		mlog(ML_HEARTBEAT, "Shutdown, node %d leaves region\n",
		     slot->ds_node_num);

		list_del_init(&slot->ds_live_item);

		अगर (list_empty(&o2hb_live_slots[slot->ds_node_num])) अणु
			clear_bit(slot->ds_node_num, o2hb_live_node_biपंचांगap);

			o2hb_queue_node_event(&event, O2HB_NODE_DOWN_CB, node,
					      slot->ds_node_num);
			queued = 1;
		पूर्ण
	पूर्ण
	spin_unlock(&o2hb_live_lock);

	अगर (queued)
		o2hb_run_event_list(&event);

	o2nm_node_put(node);
पूर्ण

अटल व्योम o2hb_set_quorum_device(काष्ठा o2hb_region *reg)
अणु
	अगर (!o2hb_global_heartbeat_active())
		वापस;

	/* Prevent race with o2hb_heartbeat_group_drop_item() */
	अगर (kthपढ़ो_should_stop())
		वापस;

	/* Tag region as quorum only after thपढ़ो reaches steady state */
	अगर (atomic_पढ़ो(&reg->hr_steady_iterations) != 0)
		वापस;

	spin_lock(&o2hb_live_lock);

	अगर (test_bit(reg->hr_region_num, o2hb_quorum_region_biपंचांगap))
		जाओ unlock;

	/*
	 * A region can be added to the quorum only when it sees all
	 * live nodes heartbeat on it. In other words, the region has been
	 * added to all nodes.
	 */
	अगर (स_भेद(reg->hr_live_node_biपंचांगap, o2hb_live_node_biपंचांगap,
		   माप(o2hb_live_node_biपंचांगap)))
		जाओ unlock;

	prपूर्णांकk(KERN_NOTICE "o2hb: Region %s (%s) is now a quorum device\n",
	       config_item_name(&reg->hr_item), reg->hr_dev_name);

	set_bit(reg->hr_region_num, o2hb_quorum_region_biपंचांगap);

	/*
	 * If global heartbeat active, unpin all regions अगर the
	 * region count > CUT_OFF
	 */
	अगर (biपंचांगap_weight(o2hb_quorum_region_biपंचांगap,
			   O2NM_MAX_REGIONS) > O2HB_PIN_CUT_OFF)
		o2hb_region_unpin(शून्य);
unlock:
	spin_unlock(&o2hb_live_lock);
पूर्ण

अटल पूर्णांक o2hb_check_slot(काष्ठा o2hb_region *reg,
			   काष्ठा o2hb_disk_slot *slot)
अणु
	पूर्णांक changed = 0, gen_changed = 0;
	काष्ठा o2hb_node_event event =
		अणु .hn_item = LIST_HEAD_INIT(event.hn_item), पूर्ण;
	काष्ठा o2nm_node *node;
	काष्ठा o2hb_disk_heartbeat_block *hb_block = reg->hr_पंचांगp_block;
	u64 cpuसमय;
	अचिन्हित पूर्णांक dead_ms = o2hb_dead_threshold * O2HB_REGION_TIMEOUT_MS;
	अचिन्हित पूर्णांक slot_dead_ms;
	पूर्णांक पंचांगp;
	पूर्णांक queued = 0;

	स_नकल(hb_block, slot->ds_raw_block, reg->hr_block_bytes);

	/*
	 * If a node is no दीर्घer configured but is still in the livemap, we
	 * may need to clear that bit from the livemap.
	 */
	node = o2nm_get_node_by_num(slot->ds_node_num);
	अगर (!node) अणु
		spin_lock(&o2hb_live_lock);
		पंचांगp = test_bit(slot->ds_node_num, o2hb_live_node_biपंचांगap);
		spin_unlock(&o2hb_live_lock);
		अगर (!पंचांगp)
			वापस 0;
	पूर्ण

	अगर (!o2hb_verअगरy_crc(reg, hb_block)) अणु
		/* all paths from here will drop o2hb_live_lock क्रम
		 * us. */
		spin_lock(&o2hb_live_lock);

		/* Don't prपूर्णांक an error on the console in this हाल -
		 * a freshly क्रमmatted heartbeat area will not have a
		 * crc set on it. */
		अगर (list_empty(&slot->ds_live_item))
			जाओ out;

		/* The node is live but pushed out a bad crc. We
		 * consider it a transient miss but करोn't populate any
		 * other values as they may be junk. */
		mlog(ML_ERROR, "Node %d has written a bad crc to %s\n",
		     slot->ds_node_num, reg->hr_dev_name);
		o2hb_dump_slot(hb_block);

		slot->ds_equal_samples++;
		जाओ fire_callbacks;
	पूर्ण

	/* we करोn't care अगर these wrap.. the state transitions below
	 * clear at the right places */
	cpuसमय = le64_to_cpu(hb_block->hb_seq);
	अगर (slot->ds_last_समय != cpuसमय)
		slot->ds_changed_samples++;
	अन्यथा
		slot->ds_equal_samples++;
	slot->ds_last_समय = cpuसमय;

	/* The node changed heartbeat generations. We assume this to
	 * mean it dropped off but came back beक्रमe we समयd out. We
	 * want to consider it करोwn क्रम the समय being but करोn't want
	 * to lose any changed_samples state we might build up to
	 * considering it live again. */
	अगर (slot->ds_last_generation != le64_to_cpu(hb_block->hb_generation)) अणु
		gen_changed = 1;
		slot->ds_equal_samples = 0;
		mlog(ML_HEARTBEAT, "Node %d changed generation (0x%llx "
		     "to 0x%llx)\n", slot->ds_node_num,
		     (दीर्घ दीर्घ)slot->ds_last_generation,
		     (दीर्घ दीर्घ)le64_to_cpu(hb_block->hb_generation));
	पूर्ण

	slot->ds_last_generation = le64_to_cpu(hb_block->hb_generation);

	mlog(ML_HEARTBEAT, "Slot %d gen 0x%llx cksum 0x%x "
	     "seq %llu last %llu changed %u equal %u\n",
	     slot->ds_node_num, (दीर्घ दीर्घ)slot->ds_last_generation,
	     le32_to_cpu(hb_block->hb_cksum),
	     (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(hb_block->hb_seq),
	     (अचिन्हित दीर्घ दीर्घ)slot->ds_last_समय, slot->ds_changed_samples,
	     slot->ds_equal_samples);

	spin_lock(&o2hb_live_lock);

fire_callbacks:
	/* dead nodes only come to lअगरe after some number of
	 * changes at any समय during their dead समय */
	अगर (list_empty(&slot->ds_live_item) &&
	    slot->ds_changed_samples >= O2HB_LIVE_THRESHOLD) अणु
		mlog(ML_HEARTBEAT, "Node %d (id 0x%llx) joined my region\n",
		     slot->ds_node_num, (दीर्घ दीर्घ)slot->ds_last_generation);

		set_bit(slot->ds_node_num, reg->hr_live_node_biपंचांगap);

		/* first on the list generates a callback */
		अगर (list_empty(&o2hb_live_slots[slot->ds_node_num])) अणु
			mlog(ML_HEARTBEAT, "o2hb: Add node %d to live nodes "
			     "bitmap\n", slot->ds_node_num);
			set_bit(slot->ds_node_num, o2hb_live_node_biपंचांगap);

			o2hb_queue_node_event(&event, O2HB_NODE_UP_CB, node,
					      slot->ds_node_num);

			changed = 1;
			queued = 1;
		पूर्ण

		list_add_tail(&slot->ds_live_item,
			      &o2hb_live_slots[slot->ds_node_num]);

		slot->ds_equal_samples = 0;

		/* We want to be sure that all nodes agree on the
		 * number of milliseconds beक्रमe a node will be
		 * considered dead. The self-fencing समयout is
		 * computed from this value, and a discrepancy might
		 * result in heartbeat calling a node dead when it
		 * hasn't self-fenced yet. */
		slot_dead_ms = le32_to_cpu(hb_block->hb_dead_ms);
		अगर (slot_dead_ms && slot_dead_ms != dead_ms) अणु
			/* TODO: Perhaps we can fail the region here. */
			mlog(ML_ERROR, "Node %d on device %s has a dead count "
			     "of %u ms, but our count is %u ms.\n"
			     "Please double check your configuration values "
			     "for 'O2CB_HEARTBEAT_THRESHOLD'\n",
			     slot->ds_node_num, reg->hr_dev_name, slot_dead_ms,
			     dead_ms);
		पूर्ण
		जाओ out;
	पूर्ण

	/* अगर the list is dead, we're करोne.. */
	अगर (list_empty(&slot->ds_live_item))
		जाओ out;

	/* live nodes only go dead after enough consequtive missed
	 * samples..  reset the missed counter whenever we see
	 * activity */
	अगर (slot->ds_equal_samples >= o2hb_dead_threshold || gen_changed) अणु
		mlog(ML_HEARTBEAT, "Node %d left my region\n",
		     slot->ds_node_num);

		clear_bit(slot->ds_node_num, reg->hr_live_node_biपंचांगap);

		/* last off the live_slot generates a callback */
		list_del_init(&slot->ds_live_item);
		अगर (list_empty(&o2hb_live_slots[slot->ds_node_num])) अणु
			mlog(ML_HEARTBEAT, "o2hb: Remove node %d from live "
			     "nodes bitmap\n", slot->ds_node_num);
			clear_bit(slot->ds_node_num, o2hb_live_node_biपंचांगap);

			/* node can be null */
			o2hb_queue_node_event(&event, O2HB_NODE_DOWN_CB,
					      node, slot->ds_node_num);

			changed = 1;
			queued = 1;
		पूर्ण

		/* We करोn't clear this because the node is still
		 * actually writing new blocks. */
		अगर (!gen_changed)
			slot->ds_changed_samples = 0;
		जाओ out;
	पूर्ण
	अगर (slot->ds_changed_samples) अणु
		slot->ds_changed_samples = 0;
		slot->ds_equal_samples = 0;
	पूर्ण
out:
	spin_unlock(&o2hb_live_lock);

	अगर (queued)
		o2hb_run_event_list(&event);

	अगर (node)
		o2nm_node_put(node);
	वापस changed;
पूर्ण

अटल पूर्णांक o2hb_highest_node(अचिन्हित दीर्घ *nodes, पूर्णांक numbits)
अणु
	वापस find_last_bit(nodes, numbits);
पूर्ण

अटल पूर्णांक o2hb_lowest_node(अचिन्हित दीर्घ *nodes, पूर्णांक numbits)
अणु
	वापस find_first_bit(nodes, numbits);
पूर्ण

अटल पूर्णांक o2hb_करो_disk_heartbeat(काष्ठा o2hb_region *reg)
अणु
	पूर्णांक i, ret, highest_node, lowest_node;
	पूर्णांक membership_change = 0, own_slot_ok = 0;
	अचिन्हित दीर्घ configured_nodes[BITS_TO_LONGS(O2NM_MAX_NODES)];
	अचिन्हित दीर्घ live_node_biपंचांगap[BITS_TO_LONGS(O2NM_MAX_NODES)];
	काष्ठा o2hb_bio_रुको_ctxt ग_लिखो_wc;

	ret = o2nm_configured_node_map(configured_nodes,
				       माप(configured_nodes));
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ bail;
	पूर्ण

	/*
	 * If a node is not configured but is in the livemap, we still need
	 * to पढ़ो the slot so as to be able to हटाओ it from the livemap.
	 */
	o2hb_fill_node_map(live_node_biपंचांगap, माप(live_node_biपंचांगap));
	i = -1;
	जबतक ((i = find_next_bit(live_node_biपंचांगap,
				  O2NM_MAX_NODES, i + 1)) < O2NM_MAX_NODES) अणु
		set_bit(i, configured_nodes);
	पूर्ण

	highest_node = o2hb_highest_node(configured_nodes, O2NM_MAX_NODES);
	lowest_node = o2hb_lowest_node(configured_nodes, O2NM_MAX_NODES);
	अगर (highest_node >= O2NM_MAX_NODES || lowest_node >= O2NM_MAX_NODES) अणु
		mlog(ML_NOTICE, "o2hb: No configured nodes found!\n");
		ret = -EINVAL;
		जाओ bail;
	पूर्ण

	/* No sense in पढ़ोing the slots of nodes that करोn't exist
	 * yet. Of course, अगर the node definitions have holes in them
	 * then we're पढ़ोing an empty slot anyway... Consider this
	 * best-efक्रमt. */
	ret = o2hb_पढ़ो_slots(reg, lowest_node, highest_node + 1);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ bail;
	पूर्ण

	/* With an up to date view of the slots, we can check that no
	 * other node has been improperly configured to heartbeat in
	 * our slot. */
	own_slot_ok = o2hb_check_own_slot(reg);

	/* fill in the proper info क्रम our next heartbeat */
	o2hb_prepare_block(reg, reg->hr_generation);

	ret = o2hb_issue_node_ग_लिखो(reg, &ग_लिखो_wc);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ bail;
	पूर्ण

	i = -1;
	जबतक((i = find_next_bit(configured_nodes,
				 O2NM_MAX_NODES, i + 1)) < O2NM_MAX_NODES) अणु
		membership_change |= o2hb_check_slot(reg, &reg->hr_slots[i]);
	पूर्ण

	/*
	 * We have to be sure we've advertised ourselves on disk
	 * beक्रमe we can go to steady state.  This ensures that
	 * people we find in our steady state have seen us.
	 */
	o2hb_रुको_on_io(&ग_लिखो_wc);
	अगर (ग_लिखो_wc.wc_error) अणु
		/* Do not re-arm the ग_लिखो समयout on I/O error - we
		 * can't be sure that the new block ever made it to
		 * disk */
		mlog(ML_ERROR, "Write error %d on device \"%s\"\n",
		     ग_लिखो_wc.wc_error, reg->hr_dev_name);
		ret = ग_लिखो_wc.wc_error;
		जाओ bail;
	पूर्ण

	/* Skip disarming the समयout अगर own slot has stale/bad data */
	अगर (own_slot_ok) अणु
		o2hb_set_quorum_device(reg);
		o2hb_arm_समयout(reg);
		reg->hr_last_समयout_start = jअगरfies;
	पूर्ण

bail:
	/* let the person who launched us know when things are steady */
	अगर (atomic_पढ़ो(&reg->hr_steady_iterations) != 0) अणु
		अगर (!ret && own_slot_ok && !membership_change) अणु
			अगर (atomic_dec_and_test(&reg->hr_steady_iterations))
				wake_up(&o2hb_steady_queue);
		पूर्ण
	पूर्ण

	अगर (atomic_पढ़ो(&reg->hr_steady_iterations) != 0) अणु
		अगर (atomic_dec_and_test(&reg->hr_unsteady_iterations)) अणु
			prपूर्णांकk(KERN_NOTICE "o2hb: Unable to stabilize "
			       "heartbeat on region %s (%s)\n",
			       config_item_name(&reg->hr_item),
			       reg->hr_dev_name);
			atomic_set(&reg->hr_steady_iterations, 0);
			reg->hr_पातed_start = 1;
			wake_up(&o2hb_steady_queue);
			ret = -EIO;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * we ride the region ref that the region dir holds.  beक्रमe the region
 * dir is हटाओd and drops it ref it will रुको to tear करोwn this
 * thपढ़ो.
 */
अटल पूर्णांक o2hb_thपढ़ो(व्योम *data)
अणु
	पूर्णांक i, ret;
	काष्ठा o2hb_region *reg = data;
	काष्ठा o2hb_bio_रुको_ctxt ग_लिखो_wc;
	kसमय_प्रकार beक्रमe_hb, after_hb;
	अचिन्हित पूर्णांक elapsed_msec;

	mlog(ML_HEARTBEAT|ML_KTHREAD, "hb thread running\n");

	set_user_nice(current, MIN_NICE);

	/* Pin node */
	ret = o2nm_depend_this_node();
	अगर (ret) अणु
		mlog(ML_ERROR, "Node has been deleted, ret = %d\n", ret);
		reg->hr_node_deleted = 1;
		wake_up(&o2hb_steady_queue);
		वापस 0;
	पूर्ण

	जबतक (!kthपढ़ो_should_stop() &&
	       !reg->hr_unclean_stop && !reg->hr_पातed_start) अणु
		/* We track the समय spent inside
		 * o2hb_करो_disk_heartbeat so that we aव्योम more than
		 * hr_समयout_ms between disk ग_लिखोs. On busy प्रणालीs
		 * this should result in a heartbeat which is less
		 * likely to समय itself out. */
		beक्रमe_hb = kसमय_get_real();

		ret = o2hb_करो_disk_heartbeat(reg);
		reg->hr_last_hb_status = ret;

		after_hb = kसमय_get_real();

		elapsed_msec = (अचिन्हित पूर्णांक)
				kसमय_ms_delta(after_hb, beक्रमe_hb);

		mlog(ML_HEARTBEAT,
		     "start = %lld, end = %lld, msec = %u, ret = %d\n",
		     beक्रमe_hb, after_hb, elapsed_msec, ret);

		अगर (!kthपढ़ो_should_stop() &&
		    elapsed_msec < reg->hr_समयout_ms) अणु
			/* the kthपढ़ो api has blocked संकेतs क्रम us so no
			 * need to record the वापस value. */
			msleep_पूर्णांकerruptible(reg->hr_समयout_ms - elapsed_msec);
		पूर्ण
	पूर्ण

	o2hb_disarm_समयout(reg);

	/* unclean stop is only used in very bad situation */
	क्रम(i = 0; !reg->hr_unclean_stop && i < reg->hr_blocks; i++)
		o2hb_shutकरोwn_slot(&reg->hr_slots[i]);

	/* Explicit करोwn notअगरication - aव्योम क्रमcing the other nodes
	 * to समयout on this region when we could just as easily
	 * ग_लिखो a clear generation - thus indicating to them that
	 * this node has left this region.
	 */
	अगर (!reg->hr_unclean_stop && !reg->hr_पातed_start) अणु
		o2hb_prepare_block(reg, 0);
		ret = o2hb_issue_node_ग_लिखो(reg, &ग_लिखो_wc);
		अगर (ret == 0)
			o2hb_रुको_on_io(&ग_लिखो_wc);
		अन्यथा
			mlog_त्रुटि_सं(ret);
	पूर्ण

	/* Unpin node */
	o2nm_undepend_this_node();

	mlog(ML_HEARTBEAT|ML_KTHREAD, "o2hb thread exiting\n");

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल पूर्णांक o2hb_debug_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा o2hb_debug_buf *db = inode->i_निजी;
	काष्ठा o2hb_region *reg;
	अचिन्हित दीर्घ map[BITS_TO_LONGS(O2NM_MAX_NODES)];
	अचिन्हित दीर्घ lts;
	अक्षर *buf = शून्य;
	पूर्णांक i = -1;
	पूर्णांक out = 0;

	/* max_nodes should be the largest biपंचांगap we pass here */
	BUG_ON(माप(map) < db->db_size);

	buf = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!buf)
		जाओ bail;

	चयन (db->db_type) अणु
	हाल O2HB_DB_TYPE_LIVENODES:
	हाल O2HB_DB_TYPE_LIVEREGIONS:
	हाल O2HB_DB_TYPE_QUORUMREGIONS:
	हाल O2HB_DB_TYPE_FAILEDREGIONS:
		spin_lock(&o2hb_live_lock);
		स_नकल(map, db->db_data, db->db_size);
		spin_unlock(&o2hb_live_lock);
		अवरोध;

	हाल O2HB_DB_TYPE_REGION_LIVENODES:
		spin_lock(&o2hb_live_lock);
		reg = (काष्ठा o2hb_region *)db->db_data;
		स_नकल(map, reg->hr_live_node_biपंचांगap, db->db_size);
		spin_unlock(&o2hb_live_lock);
		अवरोध;

	हाल O2HB_DB_TYPE_REGION_NUMBER:
		reg = (काष्ठा o2hb_region *)db->db_data;
		out += scnम_लिखो(buf + out, PAGE_SIZE - out, "%d\n",
				reg->hr_region_num);
		जाओ करोne;

	हाल O2HB_DB_TYPE_REGION_ELAPSED_TIME:
		reg = (काष्ठा o2hb_region *)db->db_data;
		lts = reg->hr_last_समयout_start;
		/* If 0, it has never been set beक्रमe */
		अगर (lts)
			lts = jअगरfies_to_msecs(jअगरfies - lts);
		out += scnम_लिखो(buf + out, PAGE_SIZE - out, "%lu\n", lts);
		जाओ करोne;

	हाल O2HB_DB_TYPE_REGION_PINNED:
		reg = (काष्ठा o2hb_region *)db->db_data;
		out += scnम_लिखो(buf + out, PAGE_SIZE - out, "%u\n",
				!!reg->hr_item_pinned);
		जाओ करोne;

	शेष:
		जाओ करोne;
	पूर्ण

	जबतक ((i = find_next_bit(map, db->db_len, i + 1)) < db->db_len)
		out += scnम_लिखो(buf + out, PAGE_SIZE - out, "%d ", i);
	out += scnम_लिखो(buf + out, PAGE_SIZE - out, "\n");

करोne:
	i_size_ग_लिखो(inode, out);

	file->निजी_data = buf;

	वापस 0;
bail:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक o2hb_debug_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	kमुक्त(file->निजी_data);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार o2hb_debug_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				 माप_प्रकार nbytes, loff_t *ppos)
अणु
	वापस simple_पढ़ो_from_buffer(buf, nbytes, ppos, file->निजी_data,
				       i_size_पढ़ो(file->f_mapping->host));
पूर्ण
#अन्यथा
अटल पूर्णांक o2hb_debug_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण
अटल पूर्णांक o2hb_debug_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण
अटल sमाप_प्रकार o2hb_debug_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			       माप_प्रकार nbytes, loff_t *ppos)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर  /* CONFIG_DEBUG_FS */

अटल स्थिर काष्ठा file_operations o2hb_debug_fops = अणु
	.खोलो =		o2hb_debug_खोलो,
	.release =	o2hb_debug_release,
	.पढ़ो =		o2hb_debug_पढ़ो,
	.llseek =	generic_file_llseek,
पूर्ण;

व्योम o2hb_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(o2hb_debug_dir);
	kमुक्त(o2hb_db_livenodes);
	kमुक्त(o2hb_db_liveregions);
	kमुक्त(o2hb_db_quorumregions);
	kमुक्त(o2hb_db_failedregions);
पूर्ण

अटल व्योम o2hb_debug_create(स्थिर अक्षर *name, काष्ठा dentry *dir,
			      काष्ठा o2hb_debug_buf **db, पूर्णांक db_len, पूर्णांक type,
			      पूर्णांक size, पूर्णांक len, व्योम *data)
अणु
	*db = kदो_स्मृति(db_len, GFP_KERNEL);
	अगर (!*db)
		वापस;

	(*db)->db_type = type;
	(*db)->db_size = size;
	(*db)->db_len = len;
	(*db)->db_data = data;

	debugfs_create_file(name, S_IFREG|S_IRUSR, dir, *db, &o2hb_debug_fops);
पूर्ण

अटल व्योम o2hb_debug_init(व्योम)
अणु
	o2hb_debug_dir = debugfs_create_dir(O2HB_DEBUG_सूची, शून्य);

	o2hb_debug_create(O2HB_DEBUG_LIVENODES, o2hb_debug_dir,
			  &o2hb_db_livenodes, माप(*o2hb_db_livenodes),
			  O2HB_DB_TYPE_LIVENODES, माप(o2hb_live_node_biपंचांगap),
			  O2NM_MAX_NODES, o2hb_live_node_biपंचांगap);

	o2hb_debug_create(O2HB_DEBUG_LIVEREGIONS, o2hb_debug_dir,
			  &o2hb_db_liveregions, माप(*o2hb_db_liveregions),
			  O2HB_DB_TYPE_LIVEREGIONS,
			  माप(o2hb_live_region_biपंचांगap), O2NM_MAX_REGIONS,
			  o2hb_live_region_biपंचांगap);

	o2hb_debug_create(O2HB_DEBUG_QUORUMREGIONS, o2hb_debug_dir,
			  &o2hb_db_quorumregions,
			  माप(*o2hb_db_quorumregions),
			  O2HB_DB_TYPE_QUORUMREGIONS,
			  माप(o2hb_quorum_region_biपंचांगap), O2NM_MAX_REGIONS,
			  o2hb_quorum_region_biपंचांगap);

	o2hb_debug_create(O2HB_DEBUG_FAILEDREGIONS, o2hb_debug_dir,
			  &o2hb_db_failedregions,
			  माप(*o2hb_db_failedregions),
			  O2HB_DB_TYPE_FAILEDREGIONS,
			  माप(o2hb_failed_region_biपंचांगap), O2NM_MAX_REGIONS,
			  o2hb_failed_region_biपंचांगap);
पूर्ण

व्योम o2hb_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(o2hb_callbacks); i++)
		INIT_LIST_HEAD(&o2hb_callbacks[i].list);

	क्रम (i = 0; i < ARRAY_SIZE(o2hb_live_slots); i++)
		INIT_LIST_HEAD(&o2hb_live_slots[i]);

	INIT_LIST_HEAD(&o2hb_node_events);

	स_रखो(o2hb_live_node_biपंचांगap, 0, माप(o2hb_live_node_biपंचांगap));
	स_रखो(o2hb_region_biपंचांगap, 0, माप(o2hb_region_biपंचांगap));
	स_रखो(o2hb_live_region_biपंचांगap, 0, माप(o2hb_live_region_biपंचांगap));
	स_रखो(o2hb_quorum_region_biपंचांगap, 0, माप(o2hb_quorum_region_biपंचांगap));
	स_रखो(o2hb_failed_region_biपंचांगap, 0, माप(o2hb_failed_region_biपंचांगap));

	o2hb_dependent_users = 0;

	o2hb_debug_init();
पूर्ण

/* अगर we're already in a callback then we're alपढ़ोy serialized by the sem */
अटल व्योम o2hb_fill_node_map_from_callback(अचिन्हित दीर्घ *map,
					     अचिन्हित bytes)
अणु
	BUG_ON(bytes < (BITS_TO_LONGS(O2NM_MAX_NODES) * माप(अचिन्हित दीर्घ)));

	स_नकल(map, &o2hb_live_node_biपंचांगap, bytes);
पूर्ण

/*
 * get a map of all nodes that are heartbeating in any regions
 */
व्योम o2hb_fill_node_map(अचिन्हित दीर्घ *map, अचिन्हित bytes)
अणु
	/* callers want to serialize this map and callbacks so that they
	 * can trust that they करोn't miss nodes coming to the party */
	करोwn_पढ़ो(&o2hb_callback_sem);
	spin_lock(&o2hb_live_lock);
	o2hb_fill_node_map_from_callback(map, bytes);
	spin_unlock(&o2hb_live_lock);
	up_पढ़ो(&o2hb_callback_sem);
पूर्ण
EXPORT_SYMBOL_GPL(o2hb_fill_node_map);

/*
 * heartbeat configfs bits.  The heartbeat set is a शेष set under
 * the cluster set in nodemanager.c.
 */

अटल काष्ठा o2hb_region *to_o2hb_region(काष्ठा config_item *item)
अणु
	वापस item ? container_of(item, काष्ठा o2hb_region, hr_item) : शून्य;
पूर्ण

/* drop_item only drops its ref after समाप्तing the thपढ़ो, nothing should
 * be using the region anymore.  this has to clean up any state that
 * attributes might have built up. */
अटल व्योम o2hb_region_release(काष्ठा config_item *item)
अणु
	पूर्णांक i;
	काष्ठा page *page;
	काष्ठा o2hb_region *reg = to_o2hb_region(item);

	mlog(ML_HEARTBEAT, "hb region release (%s)\n", reg->hr_dev_name);

	kमुक्त(reg->hr_पंचांगp_block);

	अगर (reg->hr_slot_data) अणु
		क्रम (i = 0; i < reg->hr_num_pages; i++) अणु
			page = reg->hr_slot_data[i];
			अगर (page)
				__मुक्त_page(page);
		पूर्ण
		kमुक्त(reg->hr_slot_data);
	पूर्ण

	अगर (reg->hr_bdev)
		blkdev_put(reg->hr_bdev, FMODE_READ|FMODE_WRITE);

	kमुक्त(reg->hr_slots);

	debugfs_हटाओ_recursive(reg->hr_debug_dir);
	kमुक्त(reg->hr_db_livenodes);
	kमुक्त(reg->hr_db_regnum);
	kमुक्त(reg->hr_db_elapsed_समय);
	kमुक्त(reg->hr_db_pinned);

	spin_lock(&o2hb_live_lock);
	list_del(&reg->hr_all_item);
	spin_unlock(&o2hb_live_lock);

	o2net_unरेजिस्टर_handler_list(&reg->hr_handler_list);
	kमुक्त(reg);
पूर्ण

अटल पूर्णांक o2hb_पढ़ो_block_input(काष्ठा o2hb_region *reg,
				 स्थिर अक्षर *page,
				 अचिन्हित दीर्घ *ret_bytes,
				 अचिन्हित पूर्णांक *ret_bits)
अणु
	अचिन्हित दीर्घ bytes;
	अक्षर *p = (अक्षर *)page;

	bytes = simple_म_से_अदीर्घ(p, &p, 0);
	अगर (!p || (*p && (*p != '\n')))
		वापस -EINVAL;

	/* Heartbeat and fs min / max block sizes are the same. */
	अगर (bytes > 4096 || bytes < 512)
		वापस -दुस्फल;
	अगर (hweight16(bytes) != 1)
		वापस -EINVAL;

	अगर (ret_bytes)
		*ret_bytes = bytes;
	अगर (ret_bits)
		*ret_bits = ffs(bytes) - 1;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार o2hb_region_block_bytes_show(काष्ठा config_item *item,
					    अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n", to_o2hb_region(item)->hr_block_bytes);
पूर्ण

अटल sमाप_प्रकार o2hb_region_block_bytes_store(काष्ठा config_item *item,
					     स्थिर अक्षर *page,
					     माप_प्रकार count)
अणु
	काष्ठा o2hb_region *reg = to_o2hb_region(item);
	पूर्णांक status;
	अचिन्हित दीर्घ block_bytes;
	अचिन्हित पूर्णांक block_bits;

	अगर (reg->hr_bdev)
		वापस -EINVAL;

	status = o2hb_पढ़ो_block_input(reg, page, &block_bytes,
				       &block_bits);
	अगर (status)
		वापस status;

	reg->hr_block_bytes = (अचिन्हित पूर्णांक)block_bytes;
	reg->hr_block_bits = block_bits;

	वापस count;
पूर्ण

अटल sमाप_प्रकार o2hb_region_start_block_show(काष्ठा config_item *item,
					    अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%llu\n", to_o2hb_region(item)->hr_start_block);
पूर्ण

अटल sमाप_प्रकार o2hb_region_start_block_store(काष्ठा config_item *item,
					     स्थिर अक्षर *page,
					     माप_प्रकार count)
अणु
	काष्ठा o2hb_region *reg = to_o2hb_region(item);
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	अक्षर *p = (अक्षर *)page;

	अगर (reg->hr_bdev)
		वापस -EINVAL;

	पंचांगp = simple_म_से_अदीर्घl(p, &p, 0);
	अगर (!p || (*p && (*p != '\n')))
		वापस -EINVAL;

	reg->hr_start_block = पंचांगp;

	वापस count;
पूर्ण

अटल sमाप_प्रकार o2hb_region_blocks_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%d\n", to_o2hb_region(item)->hr_blocks);
पूर्ण

अटल sमाप_प्रकार o2hb_region_blocks_store(काष्ठा config_item *item,
					स्थिर अक्षर *page,
					माप_प्रकार count)
अणु
	काष्ठा o2hb_region *reg = to_o2hb_region(item);
	अचिन्हित दीर्घ पंचांगp;
	अक्षर *p = (अक्षर *)page;

	अगर (reg->hr_bdev)
		वापस -EINVAL;

	पंचांगp = simple_म_से_अदीर्घ(p, &p, 0);
	अगर (!p || (*p && (*p != '\n')))
		वापस -EINVAL;

	अगर (पंचांगp > O2NM_MAX_NODES || पंचांगp == 0)
		वापस -दुस्फल;

	reg->hr_blocks = (अचिन्हित पूर्णांक)पंचांगp;

	वापस count;
पूर्ण

अटल sमाप_प्रकार o2hb_region_dev_show(काष्ठा config_item *item, अक्षर *page)
अणु
	अचिन्हित पूर्णांक ret = 0;

	अगर (to_o2hb_region(item)->hr_bdev)
		ret = प्र_लिखो(page, "%s\n", to_o2hb_region(item)->hr_dev_name);

	वापस ret;
पूर्ण

अटल व्योम o2hb_init_region_params(काष्ठा o2hb_region *reg)
अणु
	reg->hr_slots_per_page = PAGE_SIZE >> reg->hr_block_bits;
	reg->hr_समयout_ms = O2HB_REGION_TIMEOUT_MS;

	mlog(ML_HEARTBEAT, "hr_start_block = %llu, hr_blocks = %u\n",
	     reg->hr_start_block, reg->hr_blocks);
	mlog(ML_HEARTBEAT, "hr_block_bytes = %u, hr_block_bits = %u\n",
	     reg->hr_block_bytes, reg->hr_block_bits);
	mlog(ML_HEARTBEAT, "hr_timeout_ms = %u\n", reg->hr_समयout_ms);
	mlog(ML_HEARTBEAT, "dead threshold = %u\n", o2hb_dead_threshold);
पूर्ण

अटल पूर्णांक o2hb_map_slot_data(काष्ठा o2hb_region *reg)
अणु
	पूर्णांक i, j;
	अचिन्हित पूर्णांक last_slot;
	अचिन्हित पूर्णांक spp = reg->hr_slots_per_page;
	काष्ठा page *page;
	अक्षर *raw;
	काष्ठा o2hb_disk_slot *slot;

	reg->hr_पंचांगp_block = kदो_स्मृति(reg->hr_block_bytes, GFP_KERNEL);
	अगर (reg->hr_पंचांगp_block == शून्य)
		वापस -ENOMEM;

	reg->hr_slots = kसुस्मृति(reg->hr_blocks,
				माप(काष्ठा o2hb_disk_slot), GFP_KERNEL);
	अगर (reg->hr_slots == शून्य)
		वापस -ENOMEM;

	क्रम(i = 0; i < reg->hr_blocks; i++) अणु
		slot = &reg->hr_slots[i];
		slot->ds_node_num = i;
		INIT_LIST_HEAD(&slot->ds_live_item);
		slot->ds_raw_block = शून्य;
	पूर्ण

	reg->hr_num_pages = (reg->hr_blocks + spp - 1) / spp;
	mlog(ML_HEARTBEAT, "Going to require %u pages to cover %u blocks "
			   "at %u blocks per page\n",
	     reg->hr_num_pages, reg->hr_blocks, spp);

	reg->hr_slot_data = kसुस्मृति(reg->hr_num_pages, माप(काष्ठा page *),
				    GFP_KERNEL);
	अगर (!reg->hr_slot_data)
		वापस -ENOMEM;

	क्रम(i = 0; i < reg->hr_num_pages; i++) अणु
		page = alloc_page(GFP_KERNEL);
		अगर (!page)
			वापस -ENOMEM;

		reg->hr_slot_data[i] = page;

		last_slot = i * spp;
		raw = page_address(page);
		क्रम (j = 0;
		     (j < spp) && ((j + last_slot) < reg->hr_blocks);
		     j++) अणु
			BUG_ON((j + last_slot) >= reg->hr_blocks);

			slot = &reg->hr_slots[j + last_slot];
			slot->ds_raw_block =
				(काष्ठा o2hb_disk_heartbeat_block *) raw;

			raw += reg->hr_block_bytes;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Read in all the slots available and populate the tracking
 * काष्ठाures so that we can start with a baseline idea of what's
 * there. */
अटल पूर्णांक o2hb_populate_slot_data(काष्ठा o2hb_region *reg)
अणु
	पूर्णांक ret, i;
	काष्ठा o2hb_disk_slot *slot;
	काष्ठा o2hb_disk_heartbeat_block *hb_block;

	ret = o2hb_पढ़ो_slots(reg, 0, reg->hr_blocks);
	अगर (ret)
		जाओ out;

	/* We only want to get an idea of the values initially in each
	 * slot, so we करो no verअगरication - o2hb_check_slot will
	 * actually determine अगर each configured slot is valid and
	 * whether any values have changed. */
	क्रम(i = 0; i < reg->hr_blocks; i++) अणु
		slot = &reg->hr_slots[i];
		hb_block = (काष्ठा o2hb_disk_heartbeat_block *) slot->ds_raw_block;

		/* Only fill the values that o2hb_check_slot uses to
		 * determine changing slots */
		slot->ds_last_समय = le64_to_cpu(hb_block->hb_seq);
		slot->ds_last_generation = le64_to_cpu(hb_block->hb_generation);
	पूर्ण

out:
	वापस ret;
पूर्ण

/* this is acting as commit; we set up all of hr_bdev and hr_task or nothing */
अटल sमाप_प्रकार o2hb_region_dev_store(काष्ठा config_item *item,
				     स्थिर अक्षर *page,
				     माप_प्रकार count)
अणु
	काष्ठा o2hb_region *reg = to_o2hb_region(item);
	काष्ठा task_काष्ठा *hb_task;
	दीर्घ fd;
	पूर्णांक sectsize;
	अक्षर *p = (अक्षर *)page;
	काष्ठा fd f;
	sमाप_प्रकार ret = -EINVAL;
	पूर्णांक live_threshold;

	अगर (reg->hr_bdev)
		जाओ out;

	/* We can't heartbeat without having had our node number
	 * configured yet. */
	अगर (o2nm_this_node() == O2NM_MAX_NODES)
		जाओ out;

	fd = simple_म_से_दीर्घ(p, &p, 0);
	अगर (!p || (*p && (*p != '\n')))
		जाओ out;

	अगर (fd < 0 || fd >= पूर्णांक_उच्च)
		जाओ out;

	f = fdget(fd);
	अगर (f.file == शून्य)
		जाओ out;

	अगर (reg->hr_blocks == 0 || reg->hr_start_block == 0 ||
	    reg->hr_block_bytes == 0)
		जाओ out2;

	अगर (!S_ISBLK(f.file->f_mapping->host->i_mode))
		जाओ out2;

	reg->hr_bdev = blkdev_get_by_dev(f.file->f_mapping->host->i_rdev,
					 FMODE_WRITE | FMODE_READ, शून्य);
	अगर (IS_ERR(reg->hr_bdev)) अणु
		ret = PTR_ERR(reg->hr_bdev);
		reg->hr_bdev = शून्य;
		जाओ out2;
	पूर्ण

	bdevname(reg->hr_bdev, reg->hr_dev_name);

	sectsize = bdev_logical_block_size(reg->hr_bdev);
	अगर (sectsize != reg->hr_block_bytes) अणु
		mlog(ML_ERROR,
		     "blocksize %u incorrect for device, expected %d",
		     reg->hr_block_bytes, sectsize);
		ret = -EINVAL;
		जाओ out3;
	पूर्ण

	o2hb_init_region_params(reg);

	/* Generation of zero is invalid */
	करो अणु
		get_अक्रमom_bytes(&reg->hr_generation,
				 माप(reg->hr_generation));
	पूर्ण जबतक (reg->hr_generation == 0);

	ret = o2hb_map_slot_data(reg);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out3;
	पूर्ण

	ret = o2hb_populate_slot_data(reg);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out3;
	पूर्ण

	INIT_DELAYED_WORK(&reg->hr_ग_लिखो_समयout_work, o2hb_ग_लिखो_समयout);
	INIT_DELAYED_WORK(&reg->hr_nego_समयout_work, o2hb_nego_समयout);

	/*
	 * A node is considered live after it has beat LIVE_THRESHOLD
	 * बार.  We're not steady until we've given them a chance
	 * _after_ our first पढ़ो.
	 * The शेष threshold is bare minimum so as to limit the delay
	 * during mounts. For global heartbeat, the threshold द्विगुनd क्रम the
	 * first region.
	 */
	live_threshold = O2HB_LIVE_THRESHOLD;
	अगर (o2hb_global_heartbeat_active()) अणु
		spin_lock(&o2hb_live_lock);
		अगर (biपंचांगap_weight(o2hb_region_biपंचांगap, O2NM_MAX_REGIONS) == 1)
			live_threshold <<= 1;
		spin_unlock(&o2hb_live_lock);
	पूर्ण
	++live_threshold;
	atomic_set(&reg->hr_steady_iterations, live_threshold);
	/* unsteady_iterations is triple the steady_iterations */
	atomic_set(&reg->hr_unsteady_iterations, (live_threshold * 3));

	hb_task = kthपढ़ो_run(o2hb_thपढ़ो, reg, "o2hb-%s",
			      reg->hr_item.ci_name);
	अगर (IS_ERR(hb_task)) अणु
		ret = PTR_ERR(hb_task);
		mlog_त्रुटि_सं(ret);
		जाओ out3;
	पूर्ण

	spin_lock(&o2hb_live_lock);
	reg->hr_task = hb_task;
	spin_unlock(&o2hb_live_lock);

	ret = रुको_event_पूर्णांकerruptible(o2hb_steady_queue,
				atomic_पढ़ो(&reg->hr_steady_iterations) == 0 ||
				reg->hr_node_deleted);
	अगर (ret) अणु
		atomic_set(&reg->hr_steady_iterations, 0);
		reg->hr_पातed_start = 1;
	पूर्ण

	अगर (reg->hr_पातed_start) अणु
		ret = -EIO;
		जाओ out3;
	पूर्ण

	अगर (reg->hr_node_deleted) अणु
		ret = -EINVAL;
		जाओ out3;
	पूर्ण

	/* Ok, we were woken.  Make sure it wasn't by drop_item() */
	spin_lock(&o2hb_live_lock);
	hb_task = reg->hr_task;
	अगर (o2hb_global_heartbeat_active())
		set_bit(reg->hr_region_num, o2hb_live_region_biपंचांगap);
	spin_unlock(&o2hb_live_lock);

	अगर (hb_task)
		ret = count;
	अन्यथा
		ret = -EIO;

	अगर (hb_task && o2hb_global_heartbeat_active())
		prपूर्णांकk(KERN_NOTICE "o2hb: Heartbeat started on region %s (%s)\n",
		       config_item_name(&reg->hr_item), reg->hr_dev_name);

out3:
	अगर (ret < 0) अणु
		blkdev_put(reg->hr_bdev, FMODE_READ | FMODE_WRITE);
		reg->hr_bdev = शून्य;
	पूर्ण
out2:
	fdput(f);
out:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार o2hb_region_pid_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा o2hb_region *reg = to_o2hb_region(item);
	pid_t pid = 0;

	spin_lock(&o2hb_live_lock);
	अगर (reg->hr_task)
		pid = task_pid_nr(reg->hr_task);
	spin_unlock(&o2hb_live_lock);

	अगर (!pid)
		वापस 0;

	वापस प्र_लिखो(page, "%u\n", pid);
पूर्ण

CONFIGFS_ATTR(o2hb_region_, block_bytes);
CONFIGFS_ATTR(o2hb_region_, start_block);
CONFIGFS_ATTR(o2hb_region_, blocks);
CONFIGFS_ATTR(o2hb_region_, dev);
CONFIGFS_ATTR_RO(o2hb_region_, pid);

अटल काष्ठा configfs_attribute *o2hb_region_attrs[] = अणु
	&o2hb_region_attr_block_bytes,
	&o2hb_region_attr_start_block,
	&o2hb_region_attr_blocks,
	&o2hb_region_attr_dev,
	&o2hb_region_attr_pid,
	शून्य,
पूर्ण;

अटल काष्ठा configfs_item_operations o2hb_region_item_ops = अणु
	.release		= o2hb_region_release,
पूर्ण;

अटल स्थिर काष्ठा config_item_type o2hb_region_type = अणु
	.ct_item_ops	= &o2hb_region_item_ops,
	.ct_attrs	= o2hb_region_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

/* heartbeat set */

काष्ठा o2hb_heartbeat_group अणु
	काष्ठा config_group hs_group;
	/* some stuff? */
पूर्ण;

अटल काष्ठा o2hb_heartbeat_group *to_o2hb_heartbeat_group(काष्ठा config_group *group)
अणु
	वापस group ?
		container_of(group, काष्ठा o2hb_heartbeat_group, hs_group)
		: शून्य;
पूर्ण

अटल व्योम o2hb_debug_region_init(काष्ठा o2hb_region *reg,
				   काष्ठा dentry *parent)
अणु
	काष्ठा dentry *dir;

	dir = debugfs_create_dir(config_item_name(&reg->hr_item), parent);
	reg->hr_debug_dir = dir;

	o2hb_debug_create(O2HB_DEBUG_LIVENODES, dir, &(reg->hr_db_livenodes),
			  माप(*(reg->hr_db_livenodes)),
			  O2HB_DB_TYPE_REGION_LIVENODES,
			  माप(reg->hr_live_node_biपंचांगap), O2NM_MAX_NODES,
			  reg);

	o2hb_debug_create(O2HB_DEBUG_REGION_NUMBER, dir, &(reg->hr_db_regnum),
			  माप(*(reg->hr_db_regnum)),
			  O2HB_DB_TYPE_REGION_NUMBER, 0, O2NM_MAX_NODES, reg);

	o2hb_debug_create(O2HB_DEBUG_REGION_ELAPSED_TIME, dir,
			  &(reg->hr_db_elapsed_समय),
			  माप(*(reg->hr_db_elapsed_समय)),
			  O2HB_DB_TYPE_REGION_ELAPSED_TIME, 0, 0, reg);

	o2hb_debug_create(O2HB_DEBUG_REGION_PINNED, dir, &(reg->hr_db_pinned),
			  माप(*(reg->hr_db_pinned)),
			  O2HB_DB_TYPE_REGION_PINNED, 0, 0, reg);

पूर्ण

अटल काष्ठा config_item *o2hb_heartbeat_group_make_item(काष्ठा config_group *group,
							  स्थिर अक्षर *name)
अणु
	काष्ठा o2hb_region *reg = शून्य;
	पूर्णांक ret;

	reg = kzalloc(माप(काष्ठा o2hb_region), GFP_KERNEL);
	अगर (reg == शून्य)
		वापस ERR_PTR(-ENOMEM);

	अगर (म_माप(name) > O2HB_MAX_REGION_NAME_LEN) अणु
		ret = -ENAMETOOLONG;
		जाओ मुक्त;
	पूर्ण

	spin_lock(&o2hb_live_lock);
	reg->hr_region_num = 0;
	अगर (o2hb_global_heartbeat_active()) अणु
		reg->hr_region_num = find_first_zero_bit(o2hb_region_biपंचांगap,
							 O2NM_MAX_REGIONS);
		अगर (reg->hr_region_num >= O2NM_MAX_REGIONS) अणु
			spin_unlock(&o2hb_live_lock);
			ret = -EFBIG;
			जाओ मुक्त;
		पूर्ण
		set_bit(reg->hr_region_num, o2hb_region_biपंचांगap);
	पूर्ण
	list_add_tail(&reg->hr_all_item, &o2hb_all_regions);
	spin_unlock(&o2hb_live_lock);

	config_item_init_type_name(&reg->hr_item, name, &o2hb_region_type);

	/* this is the same way to generate msg key as dlm, क्रम local heartbeat,
	 * name is also the same, so make initial crc value dअगरferent to aव्योम
	 * message key conflict.
	 */
	reg->hr_key = crc32_le(reg->hr_region_num + O2NM_MAX_REGIONS,
		name, म_माप(name));
	INIT_LIST_HEAD(&reg->hr_handler_list);
	ret = o2net_रेजिस्टर_handler(O2HB_NEGO_TIMEOUT_MSG, reg->hr_key,
			माप(काष्ठा o2hb_nego_msg),
			o2hb_nego_समयout_handler,
			reg, शून्य, &reg->hr_handler_list);
	अगर (ret)
		जाओ हटाओ_item;

	ret = o2net_रेजिस्टर_handler(O2HB_NEGO_APPROVE_MSG, reg->hr_key,
			माप(काष्ठा o2hb_nego_msg),
			o2hb_nego_approve_handler,
			reg, शून्य, &reg->hr_handler_list);
	अगर (ret)
		जाओ unरेजिस्टर_handler;

	o2hb_debug_region_init(reg, o2hb_debug_dir);

	वापस &reg->hr_item;

unरेजिस्टर_handler:
	o2net_unरेजिस्टर_handler_list(&reg->hr_handler_list);
हटाओ_item:
	spin_lock(&o2hb_live_lock);
	list_del(&reg->hr_all_item);
	अगर (o2hb_global_heartbeat_active())
		clear_bit(reg->hr_region_num, o2hb_region_biपंचांगap);
	spin_unlock(&o2hb_live_lock);
मुक्त:
	kमुक्त(reg);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम o2hb_heartbeat_group_drop_item(काष्ठा config_group *group,
					   काष्ठा config_item *item)
अणु
	काष्ठा task_काष्ठा *hb_task;
	काष्ठा o2hb_region *reg = to_o2hb_region(item);
	पूर्णांक quorum_region = 0;

	/* stop the thपढ़ो when the user हटाओs the region dir */
	spin_lock(&o2hb_live_lock);
	hb_task = reg->hr_task;
	reg->hr_task = शून्य;
	reg->hr_item_dropped = 1;
	spin_unlock(&o2hb_live_lock);

	अगर (hb_task)
		kthपढ़ो_stop(hb_task);

	अगर (o2hb_global_heartbeat_active()) अणु
		spin_lock(&o2hb_live_lock);
		clear_bit(reg->hr_region_num, o2hb_region_biपंचांगap);
		clear_bit(reg->hr_region_num, o2hb_live_region_biपंचांगap);
		अगर (test_bit(reg->hr_region_num, o2hb_quorum_region_biपंचांगap))
			quorum_region = 1;
		clear_bit(reg->hr_region_num, o2hb_quorum_region_biपंचांगap);
		spin_unlock(&o2hb_live_lock);
		prपूर्णांकk(KERN_NOTICE "o2hb: Heartbeat %s on region %s (%s)\n",
		       ((atomic_पढ़ो(&reg->hr_steady_iterations) == 0) ?
			"stopped" : "start aborted"), config_item_name(item),
		       reg->hr_dev_name);
	पूर्ण

	/*
	 * If we're racing a dev_ग_लिखो(), we need to wake them.  They will
	 * check reg->hr_task
	 */
	अगर (atomic_पढ़ो(&reg->hr_steady_iterations) != 0) अणु
		reg->hr_पातed_start = 1;
		atomic_set(&reg->hr_steady_iterations, 0);
		wake_up(&o2hb_steady_queue);
	पूर्ण

	config_item_put(item);

	अगर (!o2hb_global_heartbeat_active() || !quorum_region)
		वापस;

	/*
	 * If global heartbeat active and there are dependent users,
	 * pin all regions अगर quorum region count <= CUT_OFF
	 */
	spin_lock(&o2hb_live_lock);

	अगर (!o2hb_dependent_users)
		जाओ unlock;

	अगर (biपंचांगap_weight(o2hb_quorum_region_biपंचांगap,
			   O2NM_MAX_REGIONS) <= O2HB_PIN_CUT_OFF)
		o2hb_region_pin(शून्य);

unlock:
	spin_unlock(&o2hb_live_lock);
पूर्ण

अटल sमाप_प्रकार o2hb_heartbeat_group_dead_threshold_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%u\n", o2hb_dead_threshold);
पूर्ण

अटल sमाप_प्रकार o2hb_heartbeat_group_dead_threshold_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ पंचांगp;
	अक्षर *p = (अक्षर *)page;

	पंचांगp = simple_म_से_अदीर्घ(p, &p, 10);
	अगर (!p || (*p && (*p != '\n')))
                वापस -EINVAL;

	/* this will validate ranges क्रम us. */
	o2hb_dead_threshold_set((अचिन्हित पूर्णांक) पंचांगp);

	वापस count;
पूर्ण

अटल sमाप_प्रकार o2hb_heartbeat_group_mode_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	वापस प्र_लिखो(page, "%s\n",
		       o2hb_heartbeat_mode_desc[o2hb_heartbeat_mode]);
पूर्ण

अटल sमाप_प्रकार o2hb_heartbeat_group_mode_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;
	माप_प्रकार len;

	len = (page[count - 1] == '\n') ? count - 1 : count;
	अगर (!len)
		वापस -EINVAL;

	क्रम (i = 0; i < O2HB_HEARTBEAT_NUM_MODES; ++i) अणु
		अगर (strnहालcmp(page, o2hb_heartbeat_mode_desc[i], len))
			जारी;

		ret = o2hb_global_heartbeat_mode_set(i);
		अगर (!ret)
			prपूर्णांकk(KERN_NOTICE "o2hb: Heartbeat mode set to %s\n",
			       o2hb_heartbeat_mode_desc[i]);
		वापस count;
	पूर्ण

	वापस -EINVAL;

पूर्ण

CONFIGFS_ATTR(o2hb_heartbeat_group_, dead_threshold);
CONFIGFS_ATTR(o2hb_heartbeat_group_, mode);

अटल काष्ठा configfs_attribute *o2hb_heartbeat_group_attrs[] = अणु
	&o2hb_heartbeat_group_attr_dead_threshold,
	&o2hb_heartbeat_group_attr_mode,
	शून्य,
पूर्ण;

अटल काष्ठा configfs_group_operations o2hb_heartbeat_group_group_ops = अणु
	.make_item	= o2hb_heartbeat_group_make_item,
	.drop_item	= o2hb_heartbeat_group_drop_item,
पूर्ण;

अटल स्थिर काष्ठा config_item_type o2hb_heartbeat_group_type = अणु
	.ct_group_ops	= &o2hb_heartbeat_group_group_ops,
	.ct_attrs	= o2hb_heartbeat_group_attrs,
	.ct_owner	= THIS_MODULE,
पूर्ण;

/* this is just here to aव्योम touching group in heartbeat.h which the
 * entire damn world #समावेशs */
काष्ठा config_group *o2hb_alloc_hb_set(व्योम)
अणु
	काष्ठा o2hb_heartbeat_group *hs = शून्य;
	काष्ठा config_group *ret = शून्य;

	hs = kzalloc(माप(काष्ठा o2hb_heartbeat_group), GFP_KERNEL);
	अगर (hs == शून्य)
		जाओ out;

	config_group_init_type_name(&hs->hs_group, "heartbeat",
				    &o2hb_heartbeat_group_type);

	ret = &hs->hs_group;
out:
	अगर (ret == शून्य)
		kमुक्त(hs);
	वापस ret;
पूर्ण

व्योम o2hb_मुक्त_hb_set(काष्ठा config_group *group)
अणु
	काष्ठा o2hb_heartbeat_group *hs = to_o2hb_heartbeat_group(group);
	kमुक्त(hs);
पूर्ण

/* hb callback registration and issuing */

अटल काष्ठा o2hb_callback *hbcall_from_type(क्रमागत o2hb_callback_type type)
अणु
	अगर (type == O2HB_NUM_CB)
		वापस ERR_PTR(-EINVAL);

	वापस &o2hb_callbacks[type];
पूर्ण

व्योम o2hb_setup_callback(काष्ठा o2hb_callback_func *hc,
			 क्रमागत o2hb_callback_type type,
			 o2hb_cb_func *func,
			 व्योम *data,
			 पूर्णांक priority)
अणु
	INIT_LIST_HEAD(&hc->hc_item);
	hc->hc_func = func;
	hc->hc_data = data;
	hc->hc_priority = priority;
	hc->hc_type = type;
	hc->hc_magic = O2HB_CB_MAGIC;
पूर्ण
EXPORT_SYMBOL_GPL(o2hb_setup_callback);

/*
 * In local heartbeat mode, region_uuid passed matches the dlm करोमुख्य name.
 * In global heartbeat mode, region_uuid passed is शून्य.
 *
 * In local, we only pin the matching region. In global we pin all the active
 * regions.
 */
अटल पूर्णांक o2hb_region_pin(स्थिर अक्षर *region_uuid)
अणु
	पूर्णांक ret = 0, found = 0;
	काष्ठा o2hb_region *reg;
	अक्षर *uuid;

	निश्चित_spin_locked(&o2hb_live_lock);

	list_क्रम_each_entry(reg, &o2hb_all_regions, hr_all_item) अणु
		अगर (reg->hr_item_dropped)
			जारी;

		uuid = config_item_name(&reg->hr_item);

		/* local heartbeat */
		अगर (region_uuid) अणु
			अगर (म_भेद(region_uuid, uuid))
				जारी;
			found = 1;
		पूर्ण

		अगर (reg->hr_item_pinned || reg->hr_item_dropped)
			जाओ skip_pin;

		/* Ignore ENOENT only क्रम local hb (userdlm करोमुख्य) */
		ret = o2nm_depend_item(&reg->hr_item);
		अगर (!ret) अणु
			mlog(ML_CLUSTER, "Pin region %s\n", uuid);
			reg->hr_item_pinned = 1;
		पूर्ण अन्यथा अणु
			अगर (ret == -ENOENT && found)
				ret = 0;
			अन्यथा अणु
				mlog(ML_ERROR, "Pin region %s fails with %d\n",
				     uuid, ret);
				अवरोध;
			पूर्ण
		पूर्ण
skip_pin:
		अगर (found)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * In local heartbeat mode, region_uuid passed matches the dlm करोमुख्य name.
 * In global heartbeat mode, region_uuid passed is शून्य.
 *
 * In local, we only unpin the matching region. In global we unpin all the
 * active regions.
 */
अटल व्योम o2hb_region_unpin(स्थिर अक्षर *region_uuid)
अणु
	काष्ठा o2hb_region *reg;
	अक्षर *uuid;
	पूर्णांक found = 0;

	निश्चित_spin_locked(&o2hb_live_lock);

	list_क्रम_each_entry(reg, &o2hb_all_regions, hr_all_item) अणु
		अगर (reg->hr_item_dropped)
			जारी;

		uuid = config_item_name(&reg->hr_item);
		अगर (region_uuid) अणु
			अगर (म_भेद(region_uuid, uuid))
				जारी;
			found = 1;
		पूर्ण

		अगर (reg->hr_item_pinned) अणु
			mlog(ML_CLUSTER, "Unpin region %s\n", uuid);
			o2nm_undepend_item(&reg->hr_item);
			reg->hr_item_pinned = 0;
		पूर्ण
		अगर (found)
			अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक o2hb_region_inc_user(स्थिर अक्षर *region_uuid)
अणु
	पूर्णांक ret = 0;

	spin_lock(&o2hb_live_lock);

	/* local heartbeat */
	अगर (!o2hb_global_heartbeat_active()) अणु
	    ret = o2hb_region_pin(region_uuid);
	    जाओ unlock;
	पूर्ण

	/*
	 * अगर global heartbeat active and this is the first dependent user,
	 * pin all regions अगर quorum region count <= CUT_OFF
	 */
	o2hb_dependent_users++;
	अगर (o2hb_dependent_users > 1)
		जाओ unlock;

	अगर (biपंचांगap_weight(o2hb_quorum_region_biपंचांगap,
			   O2NM_MAX_REGIONS) <= O2HB_PIN_CUT_OFF)
		ret = o2hb_region_pin(शून्य);

unlock:
	spin_unlock(&o2hb_live_lock);
	वापस ret;
पूर्ण

अटल व्योम o2hb_region_dec_user(स्थिर अक्षर *region_uuid)
अणु
	spin_lock(&o2hb_live_lock);

	/* local heartbeat */
	अगर (!o2hb_global_heartbeat_active()) अणु
	    o2hb_region_unpin(region_uuid);
	    जाओ unlock;
	पूर्ण

	/*
	 * अगर global heartbeat active and there are no dependent users,
	 * unpin all quorum regions
	 */
	o2hb_dependent_users--;
	अगर (!o2hb_dependent_users)
		o2hb_region_unpin(शून्य);

unlock:
	spin_unlock(&o2hb_live_lock);
पूर्ण

पूर्णांक o2hb_रेजिस्टर_callback(स्थिर अक्षर *region_uuid,
			   काष्ठा o2hb_callback_func *hc)
अणु
	काष्ठा o2hb_callback_func *f;
	काष्ठा o2hb_callback *hbcall;
	पूर्णांक ret;

	BUG_ON(hc->hc_magic != O2HB_CB_MAGIC);
	BUG_ON(!list_empty(&hc->hc_item));

	hbcall = hbcall_from_type(hc->hc_type);
	अगर (IS_ERR(hbcall)) अणु
		ret = PTR_ERR(hbcall);
		जाओ out;
	पूर्ण

	अगर (region_uuid) अणु
		ret = o2hb_region_inc_user(region_uuid);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	करोwn_ग_लिखो(&o2hb_callback_sem);

	list_क्रम_each_entry(f, &hbcall->list, hc_item) अणु
		अगर (hc->hc_priority < f->hc_priority) अणु
			list_add_tail(&hc->hc_item, &f->hc_item);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (list_empty(&hc->hc_item))
		list_add_tail(&hc->hc_item, &hbcall->list);

	up_ग_लिखो(&o2hb_callback_sem);
	ret = 0;
out:
	mlog(ML_CLUSTER, "returning %d on behalf of %p for funcs %p\n",
	     ret, __builtin_वापस_address(0), hc);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(o2hb_रेजिस्टर_callback);

व्योम o2hb_unरेजिस्टर_callback(स्थिर अक्षर *region_uuid,
			      काष्ठा o2hb_callback_func *hc)
अणु
	BUG_ON(hc->hc_magic != O2HB_CB_MAGIC);

	mlog(ML_CLUSTER, "on behalf of %p for funcs %p\n",
	     __builtin_वापस_address(0), hc);

	/* XXX Can this happen _with_ a region reference? */
	अगर (list_empty(&hc->hc_item))
		वापस;

	अगर (region_uuid)
		o2hb_region_dec_user(region_uuid);

	करोwn_ग_लिखो(&o2hb_callback_sem);

	list_del_init(&hc->hc_item);

	up_ग_लिखो(&o2hb_callback_sem);
पूर्ण
EXPORT_SYMBOL_GPL(o2hb_unरेजिस्टर_callback);

पूर्णांक o2hb_check_node_heartbeating_no_sem(u8 node_num)
अणु
	अचिन्हित दीर्घ testing_map[BITS_TO_LONGS(O2NM_MAX_NODES)];

	spin_lock(&o2hb_live_lock);
	o2hb_fill_node_map_from_callback(testing_map, माप(testing_map));
	spin_unlock(&o2hb_live_lock);
	अगर (!test_bit(node_num, testing_map)) अणु
		mlog(ML_HEARTBEAT,
		     "node (%u) does not have heartbeating enabled.\n",
		     node_num);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(o2hb_check_node_heartbeating_no_sem);

पूर्णांक o2hb_check_node_heartbeating_from_callback(u8 node_num)
अणु
	अचिन्हित दीर्घ testing_map[BITS_TO_LONGS(O2NM_MAX_NODES)];

	o2hb_fill_node_map_from_callback(testing_map, माप(testing_map));
	अगर (!test_bit(node_num, testing_map)) अणु
		mlog(ML_HEARTBEAT,
		     "node (%u) does not have heartbeating enabled.\n",
		     node_num);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(o2hb_check_node_heartbeating_from_callback);

/*
 * this is just a hack until we get the plumbing which flips file प्रणालीs
 * पढ़ो only and drops the hb ref instead of समाप्तing the node dead.
 */
व्योम o2hb_stop_all_regions(व्योम)
अणु
	काष्ठा o2hb_region *reg;

	mlog(ML_ERROR, "stopping heartbeat on all active regions.\n");

	spin_lock(&o2hb_live_lock);

	list_क्रम_each_entry(reg, &o2hb_all_regions, hr_all_item)
		reg->hr_unclean_stop = 1;

	spin_unlock(&o2hb_live_lock);
पूर्ण
EXPORT_SYMBOL_GPL(o2hb_stop_all_regions);

पूर्णांक o2hb_get_all_regions(अक्षर *region_uuids, u8 max_regions)
अणु
	काष्ठा o2hb_region *reg;
	पूर्णांक numregs = 0;
	अक्षर *p;

	spin_lock(&o2hb_live_lock);

	p = region_uuids;
	list_क्रम_each_entry(reg, &o2hb_all_regions, hr_all_item) अणु
		अगर (reg->hr_item_dropped)
			जारी;

		mlog(0, "Region: %s\n", config_item_name(&reg->hr_item));
		अगर (numregs < max_regions) अणु
			स_नकल(p, config_item_name(&reg->hr_item),
			       O2HB_MAX_REGION_NAME_LEN);
			p += O2HB_MAX_REGION_NAME_LEN;
		पूर्ण
		numregs++;
	पूर्ण

	spin_unlock(&o2hb_live_lock);

	वापस numregs;
पूर्ण
EXPORT_SYMBOL_GPL(o2hb_get_all_regions);

पूर्णांक o2hb_global_heartbeat_active(व्योम)
अणु
	वापस (o2hb_heartbeat_mode == O2HB_HEARTBEAT_GLOBAL);
पूर्ण
EXPORT_SYMBOL(o2hb_global_heartbeat_active);
