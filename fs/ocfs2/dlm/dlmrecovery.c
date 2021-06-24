<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dlmrecovery.c
 *
 * recovery stuff
 *
 * Copyright (C) 2004 Oracle.  All rights reserved.
 */


#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/init.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/socket.h>
#समावेश <linux/inet.h>
#समावेश <linux/समयr.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/delay.h>


#समावेश "../cluster/heartbeat.h"
#समावेश "../cluster/nodemanager.h"
#समावेश "../cluster/tcp.h"

#समावेश "dlmapi.h"
#समावेश "dlmcommon.h"
#समावेश "dlmdomain.h"

#घोषणा MLOG_MASK_PREFIX (ML_DLM|ML_DLM_RECOVERY)
#समावेश "../cluster/masklog.h"

अटल व्योम dlm_करो_local_recovery_cleanup(काष्ठा dlm_ctxt *dlm, u8 dead_node);

अटल पूर्णांक dlm_recovery_thपढ़ो(व्योम *data);
अटल पूर्णांक dlm_करो_recovery(काष्ठा dlm_ctxt *dlm);

अटल पूर्णांक dlm_pick_recovery_master(काष्ठा dlm_ctxt *dlm);
अटल पूर्णांक dlm_remaster_locks(काष्ठा dlm_ctxt *dlm, u8 dead_node);
अटल पूर्णांक dlm_init_recovery_area(काष्ठा dlm_ctxt *dlm, u8 dead_node);
अटल पूर्णांक dlm_request_all_locks(काष्ठा dlm_ctxt *dlm,
				 u8 request_from, u8 dead_node);
अटल व्योम dlm_destroy_recovery_area(काष्ठा dlm_ctxt *dlm);

अटल अंतरभूत पूर्णांक dlm_num_locks_in_lockres(काष्ठा dlm_lock_resource *res);
अटल व्योम dlm_init_migratable_lockres(काष्ठा dlm_migratable_lockres *mres,
					स्थिर अक्षर *lockname, पूर्णांक namelen,
					पूर्णांक total_locks, u64 cookie,
					u8 flags, u8 master);
अटल पूर्णांक dlm_send_mig_lockres_msg(काष्ठा dlm_ctxt *dlm,
				    काष्ठा dlm_migratable_lockres *mres,
				    u8 send_to,
				    काष्ठा dlm_lock_resource *res,
				    पूर्णांक total_locks);
अटल पूर्णांक dlm_process_recovery_data(काष्ठा dlm_ctxt *dlm,
				     काष्ठा dlm_lock_resource *res,
				     काष्ठा dlm_migratable_lockres *mres);
अटल पूर्णांक dlm_send_finalize_reco_message(काष्ठा dlm_ctxt *dlm);
अटल पूर्णांक dlm_send_all_करोne_msg(काष्ठा dlm_ctxt *dlm,
				 u8 dead_node, u8 send_to);
अटल पूर्णांक dlm_send_begin_reco_message(काष्ठा dlm_ctxt *dlm, u8 dead_node);
अटल व्योम dlm_move_reco_locks_to_list(काष्ठा dlm_ctxt *dlm,
					काष्ठा list_head *list, u8 dead_node);
अटल व्योम dlm_finish_local_lockres_recovery(काष्ठा dlm_ctxt *dlm,
					      u8 dead_node, u8 new_master);
अटल व्योम dlm_reco_ast(व्योम *astdata);
अटल व्योम dlm_reco_bast(व्योम *astdata, पूर्णांक blocked_type);
अटल व्योम dlm_reco_unlock_ast(व्योम *astdata, क्रमागत dlm_status st);
अटल व्योम dlm_request_all_locks_worker(काष्ठा dlm_work_item *item,
					 व्योम *data);
अटल व्योम dlm_mig_lockres_worker(काष्ठा dlm_work_item *item, व्योम *data);
अटल पूर्णांक dlm_lockres_master_requery(काष्ठा dlm_ctxt *dlm,
				      काष्ठा dlm_lock_resource *res,
				      u8 *real_master);

अटल u64 dlm_get_next_mig_cookie(व्योम);

अटल DEFINE_SPINLOCK(dlm_reco_state_lock);
अटल DEFINE_SPINLOCK(dlm_mig_cookie_lock);
अटल u64 dlm_mig_cookie = 1;

अटल u64 dlm_get_next_mig_cookie(व्योम)
अणु
	u64 c;
	spin_lock(&dlm_mig_cookie_lock);
	c = dlm_mig_cookie;
	अगर (dlm_mig_cookie == (~0ULL))
		dlm_mig_cookie = 1;
	अन्यथा
		dlm_mig_cookie++;
	spin_unlock(&dlm_mig_cookie_lock);
	वापस c;
पूर्ण

अटल अंतरभूत व्योम dlm_set_reco_dead_node(काष्ठा dlm_ctxt *dlm,
					  u8 dead_node)
अणु
	निश्चित_spin_locked(&dlm->spinlock);
	अगर (dlm->reco.dead_node != dead_node)
		mlog(0, "%s: changing dead_node from %u to %u\n",
		     dlm->name, dlm->reco.dead_node, dead_node);
	dlm->reco.dead_node = dead_node;
पूर्ण

अटल अंतरभूत व्योम dlm_set_reco_master(काष्ठा dlm_ctxt *dlm,
				       u8 master)
अणु
	निश्चित_spin_locked(&dlm->spinlock);
	mlog(0, "%s: changing new_master from %u to %u\n",
	     dlm->name, dlm->reco.new_master, master);
	dlm->reco.new_master = master;
पूर्ण

अटल अंतरभूत व्योम __dlm_reset_recovery(काष्ठा dlm_ctxt *dlm)
अणु
	निश्चित_spin_locked(&dlm->spinlock);
	clear_bit(dlm->reco.dead_node, dlm->recovery_map);
	dlm_set_reco_dead_node(dlm, O2NM_INVALID_NODE_NUM);
	dlm_set_reco_master(dlm, O2NM_INVALID_NODE_NUM);
पूर्ण

/* Worker function used during recovery. */
व्योम dlm_dispatch_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dlm_ctxt *dlm =
		container_of(work, काष्ठा dlm_ctxt, dispatched_work);
	LIST_HEAD(पंचांगp_list);
	काष्ठा dlm_work_item *item, *next;
	dlm_workfunc_t *workfunc;
	पूर्णांक tot=0;

	spin_lock(&dlm->work_lock);
	list_splice_init(&dlm->work_list, &पंचांगp_list);
	spin_unlock(&dlm->work_lock);

	list_क्रम_each_entry(item, &पंचांगp_list, list) अणु
		tot++;
	पूर्ण
	mlog(0, "%s: work thread has %d work items\n", dlm->name, tot);

	list_क्रम_each_entry_safe(item, next, &पंचांगp_list, list) अणु
		workfunc = item->func;
		list_del_init(&item->list);

		/* alपढ़ोy have ref on dlm to aव्योम having
		 * it disappear.  just द्विगुन-check. */
		BUG_ON(item->dlm != dlm);

		/* this is allowed to sleep and
		 * call network stuff */
		workfunc(item, item->data);

		dlm_put(dlm);
		kमुक्त(item);
	पूर्ण
पूर्ण

/*
 * RECOVERY THREAD
 */

व्योम dlm_kick_recovery_thपढ़ो(काष्ठा dlm_ctxt *dlm)
अणु
	/* wake the recovery thपढ़ो
	 * this will wake the reco thपढ़ो in one of three places
	 * 1) sleeping with no recovery happening
	 * 2) sleeping with recovery mastered अन्यथाwhere
	 * 3) recovery mastered here, रुकोing on reco data */

	wake_up(&dlm->dlm_reco_thपढ़ो_wq);
पूर्ण

/* Launch the recovery thपढ़ो */
पूर्णांक dlm_launch_recovery_thपढ़ो(काष्ठा dlm_ctxt *dlm)
अणु
	mlog(0, "starting dlm recovery thread...\n");

	dlm->dlm_reco_thपढ़ो_task = kthपढ़ो_run(dlm_recovery_thपढ़ो, dlm,
			"dlm_reco-%s", dlm->name);
	अगर (IS_ERR(dlm->dlm_reco_thपढ़ो_task)) अणु
		mlog_त्रुटि_सं(PTR_ERR(dlm->dlm_reco_thपढ़ो_task));
		dlm->dlm_reco_thपढ़ो_task = शून्य;
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम dlm_complete_recovery_thपढ़ो(काष्ठा dlm_ctxt *dlm)
अणु
	अगर (dlm->dlm_reco_thपढ़ो_task) अणु
		mlog(0, "waiting for dlm recovery thread to exit\n");
		kthपढ़ो_stop(dlm->dlm_reco_thपढ़ो_task);
		dlm->dlm_reco_thपढ़ो_task = शून्य;
	पूर्ण
पूर्ण



/*
 * this is lame, but here's how recovery works...
 * 1) all recovery thपढ़ोs cluster wide will work on recovering
 *    ONE node at a समय
 * 2) negotiate who will take over all the locks क्रम the dead node.
 *    thats right... ALL the locks.
 * 3) once a new master is chosen, everyone scans all locks
 *    and moves aside those mastered by the dead guy
 * 4) each of these locks should be locked until recovery is करोne
 * 5) the new master collects up all of secondary lock queue info
 *    one lock at a समय, क्रमcing each node to communicate back
 *    beक्रमe continuing
 * 6) each secondary lock queue responds with the full known lock info
 * 7) once the new master has run all its locks, it sends a ALLDONE!
 *    message to everyone
 * 8) upon receiving this message, the secondary queue node unlocks
 *    and responds to the ALLDONE
 * 9) once the new master माला_लो responses from everyone, he unlocks
 *    everything and recovery क्रम this dead node is करोne
 *10) go back to 2) जबतक there are still dead nodes
 *
 */

अटल व्योम dlm_prपूर्णांक_reco_node_status(काष्ठा dlm_ctxt *dlm)
अणु
	काष्ठा dlm_reco_node_data *ndata;
	काष्ठा dlm_lock_resource *res;

	mlog(ML_NOTICE, "%s(%d): recovery info, state=%s, dead=%u, master=%u\n",
	     dlm->name, task_pid_nr(dlm->dlm_reco_thपढ़ो_task),
	     dlm->reco.state & DLM_RECO_STATE_ACTIVE ? "ACTIVE" : "inactive",
	     dlm->reco.dead_node, dlm->reco.new_master);

	list_क्रम_each_entry(ndata, &dlm->reco.node_data, list) अणु
		अक्षर *st = "unknown";
		चयन (ndata->state) अणु
			हाल DLM_RECO_NODE_DATA_INIT:
				st = "init";
				अवरोध;
			हाल DLM_RECO_NODE_DATA_REQUESTING:
				st = "requesting";
				अवरोध;
			हाल DLM_RECO_NODE_DATA_DEAD:
				st = "dead";
				अवरोध;
			हाल DLM_RECO_NODE_DATA_RECEIVING:
				st = "receiving";
				अवरोध;
			हाल DLM_RECO_NODE_DATA_REQUESTED:
				st = "requested";
				अवरोध;
			हाल DLM_RECO_NODE_DATA_DONE:
				st = "done";
				अवरोध;
			हाल DLM_RECO_NODE_DATA_FINALIZE_SENT:
				st = "finalize-sent";
				अवरोध;
			शेष:
				st = "bad";
				अवरोध;
		पूर्ण
		mlog(ML_NOTICE, "%s: reco state, node %u, state=%s\n",
		     dlm->name, ndata->node_num, st);
	पूर्ण
	list_क्रम_each_entry(res, &dlm->reco.resources, recovering) अणु
		mlog(ML_NOTICE, "%s: lockres %.*s on recovering list\n",
		     dlm->name, res->lockname.len, res->lockname.name);
	पूर्ण
पूर्ण

#घोषणा DLM_RECO_THREAD_TIMEOUT_MS (5 * 1000)

अटल पूर्णांक dlm_recovery_thपढ़ो(व्योम *data)
अणु
	पूर्णांक status;
	काष्ठा dlm_ctxt *dlm = data;
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(DLM_RECO_THREAD_TIMEOUT_MS);

	mlog(0, "dlm thread running for %s...\n", dlm->name);

	जबतक (!kthपढ़ो_should_stop()) अणु
		अगर (dlm_करोमुख्य_fully_joined(dlm)) अणु
			status = dlm_करो_recovery(dlm);
			अगर (status == -EAGAIN) अणु
				/* करो not sleep, recheck immediately. */
				जारी;
			पूर्ण
			अगर (status < 0)
				mlog_त्रुटि_सं(status);
		पूर्ण

		रुको_event_पूर्णांकerruptible_समयout(dlm->dlm_reco_thपढ़ो_wq,
						 kthपढ़ो_should_stop(),
						 समयout);
	पूर्ण

	mlog(0, "quitting DLM recovery thread\n");
	वापस 0;
पूर्ण

/* वापसs true when the recovery master has contacted us */
अटल पूर्णांक dlm_reco_master_पढ़ोy(काष्ठा dlm_ctxt *dlm)
अणु
	पूर्णांक पढ़ोy;
	spin_lock(&dlm->spinlock);
	पढ़ोy = (dlm->reco.new_master != O2NM_INVALID_NODE_NUM);
	spin_unlock(&dlm->spinlock);
	वापस पढ़ोy;
पूर्ण

/* वापसs true अगर node is no दीर्घer in the करोमुख्य
 * could be dead or just not joined */
पूर्णांक dlm_is_node_dead(काष्ठा dlm_ctxt *dlm, u8 node)
अणु
	पूर्णांक dead;
	spin_lock(&dlm->spinlock);
	dead = !test_bit(node, dlm->करोमुख्य_map);
	spin_unlock(&dlm->spinlock);
	वापस dead;
पूर्ण

/* वापसs true अगर node is no दीर्घer in the करोमुख्य
 * could be dead or just not joined */
अटल पूर्णांक dlm_is_node_recovered(काष्ठा dlm_ctxt *dlm, u8 node)
अणु
	पूर्णांक recovered;
	spin_lock(&dlm->spinlock);
	recovered = !test_bit(node, dlm->recovery_map);
	spin_unlock(&dlm->spinlock);
	वापस recovered;
पूर्ण


व्योम dlm_रुको_क्रम_node_death(काष्ठा dlm_ctxt *dlm, u8 node, पूर्णांक समयout)
अणु
	अगर (dlm_is_node_dead(dlm, node))
		वापस;

	prपूर्णांकk(KERN_NOTICE "o2dlm: Waiting on the death of node %u in "
	       "domain %s\n", node, dlm->name);

	अगर (समयout)
		रुको_event_समयout(dlm->dlm_reco_thपढ़ो_wq,
				   dlm_is_node_dead(dlm, node),
				   msecs_to_jअगरfies(समयout));
	अन्यथा
		रुको_event(dlm->dlm_reco_thपढ़ो_wq,
			   dlm_is_node_dead(dlm, node));
पूर्ण

व्योम dlm_रुको_क्रम_node_recovery(काष्ठा dlm_ctxt *dlm, u8 node, पूर्णांक समयout)
अणु
	अगर (dlm_is_node_recovered(dlm, node))
		वापस;

	prपूर्णांकk(KERN_NOTICE "o2dlm: Waiting on the recovery of node %u in "
	       "domain %s\n", node, dlm->name);

	अगर (समयout)
		रुको_event_समयout(dlm->dlm_reco_thपढ़ो_wq,
				   dlm_is_node_recovered(dlm, node),
				   msecs_to_jअगरfies(समयout));
	अन्यथा
		रुको_event(dlm->dlm_reco_thपढ़ो_wq,
			   dlm_is_node_recovered(dlm, node));
पूर्ण

/* callers of the top-level api calls (dlmlock/dlmunlock) should
 * block on the dlm->reco.event when recovery is in progress.
 * the dlm recovery thपढ़ो will set this state when it begins
 * recovering a dead node (as the new master or not) and clear
 * the state and wake as soon as all affected lock resources have
 * been marked with the RECOVERY flag */
अटल पूर्णांक dlm_in_recovery(काष्ठा dlm_ctxt *dlm)
अणु
	पूर्णांक in_recovery;
	spin_lock(&dlm->spinlock);
	in_recovery = !!(dlm->reco.state & DLM_RECO_STATE_ACTIVE);
	spin_unlock(&dlm->spinlock);
	वापस in_recovery;
पूर्ण


व्योम dlm_रुको_क्रम_recovery(काष्ठा dlm_ctxt *dlm)
अणु
	अगर (dlm_in_recovery(dlm)) अणु
		mlog(0, "%s: reco thread %d in recovery: "
		     "state=%d, master=%u, dead=%u\n",
		     dlm->name, task_pid_nr(dlm->dlm_reco_thपढ़ो_task),
		     dlm->reco.state, dlm->reco.new_master,
		     dlm->reco.dead_node);
	पूर्ण
	रुको_event(dlm->reco.event, !dlm_in_recovery(dlm));
पूर्ण

अटल व्योम dlm_begin_recovery(काष्ठा dlm_ctxt *dlm)
अणु
	निश्चित_spin_locked(&dlm->spinlock);
	BUG_ON(dlm->reco.state & DLM_RECO_STATE_ACTIVE);
	prपूर्णांकk(KERN_NOTICE "o2dlm: Begin recovery on domain %s for node %u\n",
	       dlm->name, dlm->reco.dead_node);
	dlm->reco.state |= DLM_RECO_STATE_ACTIVE;
पूर्ण

अटल व्योम dlm_end_recovery(काष्ठा dlm_ctxt *dlm)
अणु
	spin_lock(&dlm->spinlock);
	BUG_ON(!(dlm->reco.state & DLM_RECO_STATE_ACTIVE));
	dlm->reco.state &= ~DLM_RECO_STATE_ACTIVE;
	spin_unlock(&dlm->spinlock);
	prपूर्णांकk(KERN_NOTICE "o2dlm: End recovery on domain %s\n", dlm->name);
	wake_up(&dlm->reco.event);
पूर्ण

अटल व्योम dlm_prपूर्णांक_recovery_master(काष्ठा dlm_ctxt *dlm)
अणु
	prपूर्णांकk(KERN_NOTICE "o2dlm: Node %u (%s) is the Recovery Master for the "
	       "dead node %u in domain %s\n", dlm->reco.new_master,
	       (dlm->node_num == dlm->reco.new_master ? "me" : "he"),
	       dlm->reco.dead_node, dlm->name);
पूर्ण

अटल पूर्णांक dlm_करो_recovery(काष्ठा dlm_ctxt *dlm)
अणु
	पूर्णांक status = 0;
	पूर्णांक ret;

	spin_lock(&dlm->spinlock);

	अगर (dlm->migrate_करोne) अणु
		mlog(0, "%s: no need do recovery after migrating all "
		     "lock resources\n", dlm->name);
		spin_unlock(&dlm->spinlock);
		वापस 0;
	पूर्ण

	/* check to see अगर the new master has died */
	अगर (dlm->reco.new_master != O2NM_INVALID_NODE_NUM &&
	    test_bit(dlm->reco.new_master, dlm->recovery_map)) अणु
		mlog(0, "new master %u died while recovering %u!\n",
		     dlm->reco.new_master, dlm->reco.dead_node);
		/* unset the new_master, leave dead_node */
		dlm_set_reco_master(dlm, O2NM_INVALID_NODE_NUM);
	पूर्ण

	/* select a target to recover */
	अगर (dlm->reco.dead_node == O2NM_INVALID_NODE_NUM) अणु
		पूर्णांक bit;

		bit = find_next_bit (dlm->recovery_map, O2NM_MAX_NODES, 0);
		अगर (bit >= O2NM_MAX_NODES || bit < 0)
			dlm_set_reco_dead_node(dlm, O2NM_INVALID_NODE_NUM);
		अन्यथा
			dlm_set_reco_dead_node(dlm, bit);
	पूर्ण अन्यथा अगर (!test_bit(dlm->reco.dead_node, dlm->recovery_map)) अणु
		/* BUG? */
		mlog(ML_ERROR, "dead_node %u no longer in recovery map!\n",
		     dlm->reco.dead_node);
		dlm_set_reco_dead_node(dlm, O2NM_INVALID_NODE_NUM);
	पूर्ण

	अगर (dlm->reco.dead_node == O2NM_INVALID_NODE_NUM) अणु
		// mlog(0, "nothing to recover!  sleeping now!\n");
		spin_unlock(&dlm->spinlock);
		/* वापस to मुख्य thपढ़ो loop and sleep. */
		वापस 0;
	पूर्ण
	mlog(0, "%s(%d):recovery thread found node %u in the recovery map!\n",
	     dlm->name, task_pid_nr(dlm->dlm_reco_thपढ़ो_task),
	     dlm->reco.dead_node);

	/* take ग_लिखो barrier */
	/* (stops the list reshuffling thपढ़ो, proxy ast handling) */
	dlm_begin_recovery(dlm);

	spin_unlock(&dlm->spinlock);

	अगर (dlm->reco.new_master == dlm->node_num)
		जाओ master_here;

	अगर (dlm->reco.new_master == O2NM_INVALID_NODE_NUM) अणु
		/* choose a new master, वापसs 0 अगर this node
		 * is the master, -EEXIST अगर it's another node.
		 * this करोes not वापस until a new master is chosen
		 * or recovery completes entirely. */
		ret = dlm_pick_recovery_master(dlm);
		अगर (!ret) अणु
			/* alपढ़ोy notअगरied everyone.  go. */
			जाओ master_here;
		पूर्ण
		mlog(0, "another node will master this recovery session.\n");
	पूर्ण

	dlm_prपूर्णांक_recovery_master(dlm);

	/* it is safe to start everything back up here
	 * because all of the dead node's lock resources
	 * have been marked as in-recovery */
	dlm_end_recovery(dlm);

	/* sleep out in मुख्य dlm_recovery_thपढ़ो loop. */
	वापस 0;

master_here:
	dlm_prपूर्णांक_recovery_master(dlm);

	status = dlm_remaster_locks(dlm, dlm->reco.dead_node);
	अगर (status < 0) अणु
		/* we should never hit this anymore */
		mlog(ML_ERROR, "%s: Error %d remastering locks for node %u, "
		     "retrying.\n", dlm->name, status, dlm->reco.dead_node);
		/* yield a bit to allow any final network messages
		 * to get handled on reमुख्यing nodes */
		msleep(100);
	पूर्ण अन्यथा अणु
		/* success!  see अगर any other nodes need recovery */
		mlog(0, "DONE mastering recovery of %s:%u here(this=%u)!\n",
		     dlm->name, dlm->reco.dead_node, dlm->node_num);
		spin_lock(&dlm->spinlock);
		__dlm_reset_recovery(dlm);
		dlm->reco.state &= ~DLM_RECO_STATE_FINALIZE;
		spin_unlock(&dlm->spinlock);
	पूर्ण
	dlm_end_recovery(dlm);

	/* जारी and look क्रम another dead node */
	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक dlm_remaster_locks(काष्ठा dlm_ctxt *dlm, u8 dead_node)
अणु
	पूर्णांक status = 0;
	काष्ठा dlm_reco_node_data *ndata;
	पूर्णांक all_nodes_करोne;
	पूर्णांक destroy = 0;
	पूर्णांक pass = 0;

	करो अणु
		/* we have become recovery master.  there is no escaping
		 * this, so just keep trying until we get it. */
		status = dlm_init_recovery_area(dlm, dead_node);
		अगर (status < 0) अणु
			mlog(ML_ERROR, "%s: failed to alloc recovery area, "
			     "retrying\n", dlm->name);
			msleep(1000);
		पूर्ण
	पूर्ण जबतक (status != 0);

	/* safe to access the node data list without a lock, since this
	 * process is the only one to change the list */
	list_क्रम_each_entry(ndata, &dlm->reco.node_data, list) अणु
		BUG_ON(ndata->state != DLM_RECO_NODE_DATA_INIT);
		ndata->state = DLM_RECO_NODE_DATA_REQUESTING;

		mlog(0, "%s: Requesting lock info from node %u\n", dlm->name,
		     ndata->node_num);

		अगर (ndata->node_num == dlm->node_num) अणु
			ndata->state = DLM_RECO_NODE_DATA_DONE;
			जारी;
		पूर्ण

		करो अणु
			status = dlm_request_all_locks(dlm, ndata->node_num,
						       dead_node);
			अगर (status < 0) अणु
				mlog_त्रुटि_सं(status);
				अगर (dlm_is_host_करोwn(status)) अणु
					/* node died, ignore it क्रम recovery */
					status = 0;
					ndata->state = DLM_RECO_NODE_DATA_DEAD;
					/* रुको क्रम the करोमुख्य map to catch up
					 * with the network state. */
					रुको_event_समयout(dlm->dlm_reco_thपढ़ो_wq,
							   dlm_is_node_dead(dlm,
								ndata->node_num),
							   msecs_to_jअगरfies(1000));
					mlog(0, "waited 1 sec for %u, "
					     "dead? %s\n", ndata->node_num,
					     dlm_is_node_dead(dlm, ndata->node_num) ?
					     "yes" : "no");
				पूर्ण अन्यथा अणु
					/* -ENOMEM on the other node */
					mlog(0, "%s: node %u returned "
					     "%d during recovery, retrying "
					     "after a short wait\n",
					     dlm->name, ndata->node_num,
					     status);
					msleep(100);
				पूर्ण
			पूर्ण
		पूर्ण जबतक (status != 0);

		spin_lock(&dlm_reco_state_lock);
		चयन (ndata->state) अणु
			हाल DLM_RECO_NODE_DATA_INIT:
			हाल DLM_RECO_NODE_DATA_FINALIZE_SENT:
			हाल DLM_RECO_NODE_DATA_REQUESTED:
				BUG();
				अवरोध;
			हाल DLM_RECO_NODE_DATA_DEAD:
				mlog(0, "node %u died after requesting "
				     "recovery info for node %u\n",
				     ndata->node_num, dead_node);
				/* fine.  करोn't need this node's info.
				 * जारी without it. */
				अवरोध;
			हाल DLM_RECO_NODE_DATA_REQUESTING:
				ndata->state = DLM_RECO_NODE_DATA_REQUESTED;
				mlog(0, "now receiving recovery data from "
				     "node %u for dead node %u\n",
				     ndata->node_num, dead_node);
				अवरोध;
			हाल DLM_RECO_NODE_DATA_RECEIVING:
				mlog(0, "already receiving recovery data from "
				     "node %u for dead node %u\n",
				     ndata->node_num, dead_node);
				अवरोध;
			हाल DLM_RECO_NODE_DATA_DONE:
				mlog(0, "already DONE receiving recovery data "
				     "from node %u for dead node %u\n",
				     ndata->node_num, dead_node);
				अवरोध;
		पूर्ण
		spin_unlock(&dlm_reco_state_lock);
	पूर्ण

	mlog(0, "%s: Done requesting all lock info\n", dlm->name);

	/* nodes should be sending reco data now
	 * just need to रुको */

	जबतक (1) अणु
		/* check all the nodes now to see अगर we are
		 * करोne, or अगर anyone died */
		all_nodes_करोne = 1;
		spin_lock(&dlm_reco_state_lock);
		list_क्रम_each_entry(ndata, &dlm->reco.node_data, list) अणु
			mlog(0, "checking recovery state of node %u\n",
			     ndata->node_num);
			चयन (ndata->state) अणु
				हाल DLM_RECO_NODE_DATA_INIT:
				हाल DLM_RECO_NODE_DATA_REQUESTING:
					mlog(ML_ERROR, "bad ndata state for "
					     "node %u: state=%d\n",
					     ndata->node_num, ndata->state);
					BUG();
					अवरोध;
				हाल DLM_RECO_NODE_DATA_DEAD:
					mlog(0, "node %u died after "
					     "requesting recovery info for "
					     "node %u\n", ndata->node_num,
					     dead_node);
					अवरोध;
				हाल DLM_RECO_NODE_DATA_RECEIVING:
				हाल DLM_RECO_NODE_DATA_REQUESTED:
					mlog(0, "%s: node %u still in state %s\n",
					     dlm->name, ndata->node_num,
					     ndata->state==DLM_RECO_NODE_DATA_RECEIVING ?
					     "receiving" : "requested");
					all_nodes_करोne = 0;
					अवरोध;
				हाल DLM_RECO_NODE_DATA_DONE:
					mlog(0, "%s: node %u state is done\n",
					     dlm->name, ndata->node_num);
					अवरोध;
				हाल DLM_RECO_NODE_DATA_FINALIZE_SENT:
					mlog(0, "%s: node %u state is finalize\n",
					     dlm->name, ndata->node_num);
					अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock(&dlm_reco_state_lock);

		mlog(0, "pass #%d, all_nodes_done?: %s\n", ++pass,
		     all_nodes_करोne?"yes":"no");
		अगर (all_nodes_करोne) अणु
			पूर्णांक ret;

			/* Set this flag on recovery master to aव्योम
			 * a new recovery क्रम another dead node start
			 * beक्रमe the recovery is not करोne. That may
			 * cause recovery hung.*/
			spin_lock(&dlm->spinlock);
			dlm->reco.state |= DLM_RECO_STATE_FINALIZE;
			spin_unlock(&dlm->spinlock);

			/* all nodes are now in DLM_RECO_NODE_DATA_DONE state
	 		 * just send a finalize message to everyone and
	 		 * clean up */
			mlog(0, "all nodes are done! send finalize\n");
			ret = dlm_send_finalize_reco_message(dlm);
			अगर (ret < 0)
				mlog_त्रुटि_सं(ret);

			spin_lock(&dlm->spinlock);
			dlm_finish_local_lockres_recovery(dlm, dead_node,
							  dlm->node_num);
			spin_unlock(&dlm->spinlock);
			mlog(0, "should be done with recovery!\n");

			mlog(0, "finishing recovery of %s at %lu, "
			     "dead=%u, this=%u, new=%u\n", dlm->name,
			     jअगरfies, dlm->reco.dead_node,
			     dlm->node_num, dlm->reco.new_master);
			destroy = 1;
			status = 0;
			/* rescan everything marked dirty aदीर्घ the way */
			dlm_kick_thपढ़ो(dlm, शून्य);
			अवरोध;
		पूर्ण
		/* रुको to be संकेतled, with periodic समयout
		 * to check क्रम node death */
		रुको_event_पूर्णांकerruptible_समयout(dlm->dlm_reco_thपढ़ो_wq,
					 kthपढ़ो_should_stop(),
					 msecs_to_jअगरfies(DLM_RECO_THREAD_TIMEOUT_MS));

	पूर्ण

	अगर (destroy)
		dlm_destroy_recovery_area(dlm);

	वापस status;
पूर्ण

अटल पूर्णांक dlm_init_recovery_area(काष्ठा dlm_ctxt *dlm, u8 dead_node)
अणु
	पूर्णांक num=0;
	काष्ठा dlm_reco_node_data *ndata;

	spin_lock(&dlm->spinlock);
	स_नकल(dlm->reco.node_map, dlm->करोमुख्य_map, माप(dlm->करोमुख्य_map));
	/* nodes can only be हटाओd (by dying) after dropping
	 * this lock, and death will be trapped later, so this should करो */
	spin_unlock(&dlm->spinlock);

	जबतक (1) अणु
		num = find_next_bit (dlm->reco.node_map, O2NM_MAX_NODES, num);
		अगर (num >= O2NM_MAX_NODES) अणु
			अवरोध;
		पूर्ण
		BUG_ON(num == dead_node);

		ndata = kzalloc(माप(*ndata), GFP_NOFS);
		अगर (!ndata) अणु
			dlm_destroy_recovery_area(dlm);
			वापस -ENOMEM;
		पूर्ण
		ndata->node_num = num;
		ndata->state = DLM_RECO_NODE_DATA_INIT;
		spin_lock(&dlm_reco_state_lock);
		list_add_tail(&ndata->list, &dlm->reco.node_data);
		spin_unlock(&dlm_reco_state_lock);
		num++;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dlm_destroy_recovery_area(काष्ठा dlm_ctxt *dlm)
अणु
	काष्ठा dlm_reco_node_data *ndata, *next;
	LIST_HEAD(पंचांगplist);

	spin_lock(&dlm_reco_state_lock);
	list_splice_init(&dlm->reco.node_data, &पंचांगplist);
	spin_unlock(&dlm_reco_state_lock);

	list_क्रम_each_entry_safe(ndata, next, &पंचांगplist, list) अणु
		list_del_init(&ndata->list);
		kमुक्त(ndata);
	पूर्ण
पूर्ण

अटल पूर्णांक dlm_request_all_locks(काष्ठा dlm_ctxt *dlm, u8 request_from,
				 u8 dead_node)
अणु
	काष्ठा dlm_lock_request lr;
	पूर्णांक ret;
	पूर्णांक status;

	mlog(0, "\n");


	mlog(0, "dlm_request_all_locks: dead node is %u, sending request "
		  "to %u\n", dead_node, request_from);

	स_रखो(&lr, 0, माप(lr));
	lr.node_idx = dlm->node_num;
	lr.dead_node = dead_node;

	// send message
	ret = o2net_send_message(DLM_LOCK_REQUEST_MSG, dlm->key,
				 &lr, माप(lr), request_from, &status);

	/* negative status is handled by caller */
	अगर (ret < 0)
		mlog(ML_ERROR, "%s: Error %d send LOCK_REQUEST to node %u "
		     "to recover dead node %u\n", dlm->name, ret,
		     request_from, dead_node);
	अन्यथा
		ret = status;
	// वापस from here, then
	// sleep until all received or error
	वापस ret;

पूर्ण

पूर्णांक dlm_request_all_locks_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
				  व्योम **ret_data)
अणु
	काष्ठा dlm_ctxt *dlm = data;
	काष्ठा dlm_lock_request *lr = (काष्ठा dlm_lock_request *)msg->buf;
	अक्षर *buf = शून्य;
	काष्ठा dlm_work_item *item = शून्य;

	अगर (!dlm_grab(dlm))
		वापस -EINVAL;

	अगर (lr->dead_node != dlm->reco.dead_node) अणु
		mlog(ML_ERROR, "%s: node %u sent dead_node=%u, but local "
		     "dead_node is %u\n", dlm->name, lr->node_idx,
		     lr->dead_node, dlm->reco.dead_node);
		dlm_prपूर्णांक_reco_node_status(dlm);
		/* this is a hack */
		dlm_put(dlm);
		वापस -ENOMEM;
	पूर्ण
	BUG_ON(lr->dead_node != dlm->reco.dead_node);

	item = kzalloc(माप(*item), GFP_NOFS);
	अगर (!item) अणु
		dlm_put(dlm);
		वापस -ENOMEM;
	पूर्ण

	/* this will get मुक्तd by dlm_request_all_locks_worker */
	buf = (अक्षर *) __get_मुक्त_page(GFP_NOFS);
	अगर (!buf) अणु
		kमुक्त(item);
		dlm_put(dlm);
		वापस -ENOMEM;
	पूर्ण

	/* queue up work क्रम dlm_request_all_locks_worker */
	dlm_grab(dlm);  /* get an extra ref क्रम the work item */
	dlm_init_work_item(dlm, item, dlm_request_all_locks_worker, buf);
	item->u.ral.reco_master = lr->node_idx;
	item->u.ral.dead_node = lr->dead_node;
	spin_lock(&dlm->work_lock);
	list_add_tail(&item->list, &dlm->work_list);
	spin_unlock(&dlm->work_lock);
	queue_work(dlm->dlm_worker, &dlm->dispatched_work);

	dlm_put(dlm);
	वापस 0;
पूर्ण

अटल व्योम dlm_request_all_locks_worker(काष्ठा dlm_work_item *item, व्योम *data)
अणु
	काष्ठा dlm_migratable_lockres *mres;
	काष्ठा dlm_lock_resource *res;
	काष्ठा dlm_ctxt *dlm;
	LIST_HEAD(resources);
	पूर्णांक ret;
	u8 dead_node, reco_master;
	पूर्णांक skip_all_करोne = 0;

	dlm = item->dlm;
	dead_node = item->u.ral.dead_node;
	reco_master = item->u.ral.reco_master;
	mres = (काष्ठा dlm_migratable_lockres *)data;

	mlog(0, "%s: recovery worker started, dead=%u, master=%u\n",
	     dlm->name, dead_node, reco_master);

	अगर (dead_node != dlm->reco.dead_node ||
	    reco_master != dlm->reco.new_master) अणु
		/* worker could have been created beक्रमe the recovery master
		 * died.  अगर so, करो not जारी, but करो not error. */
		अगर (dlm->reco.new_master == O2NM_INVALID_NODE_NUM) अणु
			mlog(ML_NOTICE, "%s: will not send recovery state, "
			     "recovery master %u died, thread=(dead=%u,mas=%u)"
			     " current=(dead=%u,mas=%u)\n", dlm->name,
			     reco_master, dead_node, reco_master,
			     dlm->reco.dead_node, dlm->reco.new_master);
		पूर्ण अन्यथा अणु
			mlog(ML_NOTICE, "%s: reco state invalid: reco(dead=%u, "
			     "master=%u), request(dead=%u, master=%u)\n",
			     dlm->name, dlm->reco.dead_node,
			     dlm->reco.new_master, dead_node, reco_master);
		पूर्ण
		जाओ leave;
	पूर्ण

	/* lock resources should have alपढ़ोy been moved to the
 	 * dlm->reco.resources list.  now move items from that list
 	 * to a temp list अगर the dead owner matches.  note that the
	 * whole cluster recovers only one node at a समय, so we
	 * can safely move UNKNOWN lock resources क्रम each recovery
	 * session. */
	dlm_move_reco_locks_to_list(dlm, &resources, dead_node);

	/* now we can begin blasting lockreses without the dlm lock */

	/* any errors वापसed will be due to the new_master dying,
	 * the dlm_reco_thपढ़ो should detect this */
	list_क्रम_each_entry(res, &resources, recovering) अणु
		ret = dlm_send_one_lockres(dlm, res, mres, reco_master,
				   	DLM_MRES_RECOVERY);
		अगर (ret < 0) अणु
			mlog(ML_ERROR, "%s: node %u went down while sending "
			     "recovery state for dead node %u, ret=%d\n", dlm->name,
			     reco_master, dead_node, ret);
			skip_all_करोne = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	/* move the resources back to the list */
	spin_lock(&dlm->spinlock);
	list_splice_init(&resources, &dlm->reco.resources);
	spin_unlock(&dlm->spinlock);

	अगर (!skip_all_करोne) अणु
		ret = dlm_send_all_करोne_msg(dlm, dead_node, reco_master);
		अगर (ret < 0) अणु
			mlog(ML_ERROR, "%s: node %u went down while sending "
			     "recovery all-done for dead node %u, ret=%d\n",
			     dlm->name, reco_master, dead_node, ret);
		पूर्ण
	पूर्ण
leave:
	मुक्त_page((अचिन्हित दीर्घ)data);
पूर्ण


अटल पूर्णांक dlm_send_all_करोne_msg(काष्ठा dlm_ctxt *dlm, u8 dead_node, u8 send_to)
अणु
	पूर्णांक ret, पंचांगpret;
	काष्ठा dlm_reco_data_करोne करोne_msg;

	स_रखो(&करोne_msg, 0, माप(करोne_msg));
	करोne_msg.node_idx = dlm->node_num;
	करोne_msg.dead_node = dead_node;
	mlog(0, "sending DATA DONE message to %u, "
	     "my node=%u, dead node=%u\n", send_to, करोne_msg.node_idx,
	     करोne_msg.dead_node);

	ret = o2net_send_message(DLM_RECO_DATA_DONE_MSG, dlm->key, &करोne_msg,
				 माप(करोne_msg), send_to, &पंचांगpret);
	अगर (ret < 0) अणु
		mlog(ML_ERROR, "%s: Error %d send RECO_DATA_DONE to node %u "
		     "to recover dead node %u\n", dlm->name, ret, send_to,
		     dead_node);
		अगर (!dlm_is_host_करोwn(ret)) अणु
			BUG();
		पूर्ण
	पूर्ण अन्यथा
		ret = पंचांगpret;
	वापस ret;
पूर्ण


पूर्णांक dlm_reco_data_करोne_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			       व्योम **ret_data)
अणु
	काष्ठा dlm_ctxt *dlm = data;
	काष्ठा dlm_reco_data_करोne *करोne = (काष्ठा dlm_reco_data_करोne *)msg->buf;
	काष्ठा dlm_reco_node_data *ndata = शून्य;
	पूर्णांक ret = -EINVAL;

	अगर (!dlm_grab(dlm))
		वापस -EINVAL;

	mlog(0, "got DATA DONE: dead_node=%u, reco.dead_node=%u, "
	     "node_idx=%u, this node=%u\n", करोne->dead_node,
	     dlm->reco.dead_node, करोne->node_idx, dlm->node_num);

	mlog_bug_on_msg((करोne->dead_node != dlm->reco.dead_node),
			"Got DATA DONE: dead_node=%u, reco.dead_node=%u, "
			"node_idx=%u, this node=%u\n", करोne->dead_node,
			dlm->reco.dead_node, करोne->node_idx, dlm->node_num);

	spin_lock(&dlm_reco_state_lock);
	list_क्रम_each_entry(ndata, &dlm->reco.node_data, list) अणु
		अगर (ndata->node_num != करोne->node_idx)
			जारी;

		चयन (ndata->state) अणु
			/* should have moved beyond INIT but not to FINALIZE yet */
			हाल DLM_RECO_NODE_DATA_INIT:
			हाल DLM_RECO_NODE_DATA_DEAD:
			हाल DLM_RECO_NODE_DATA_FINALIZE_SENT:
				mlog(ML_ERROR, "bad ndata state for node %u:"
				     " state=%d\n", ndata->node_num,
				     ndata->state);
				BUG();
				अवरोध;
			/* these states are possible at this poपूर्णांक, anywhere aदीर्घ
			 * the line of recovery */
			हाल DLM_RECO_NODE_DATA_DONE:
			हाल DLM_RECO_NODE_DATA_RECEIVING:
			हाल DLM_RECO_NODE_DATA_REQUESTED:
			हाल DLM_RECO_NODE_DATA_REQUESTING:
				mlog(0, "node %u is DONE sending "
					  "recovery data!\n",
					  ndata->node_num);

				ndata->state = DLM_RECO_NODE_DATA_DONE;
				ret = 0;
				अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&dlm_reco_state_lock);

	/* wake the recovery thपढ़ो, some node is करोne */
	अगर (!ret)
		dlm_kick_recovery_thपढ़ो(dlm);

	अगर (ret < 0)
		mlog(ML_ERROR, "failed to find recovery node data for node "
		     "%u\n", करोne->node_idx);
	dlm_put(dlm);

	mlog(0, "leaving reco data done handler, ret=%d\n", ret);
	वापस ret;
पूर्ण

अटल व्योम dlm_move_reco_locks_to_list(काष्ठा dlm_ctxt *dlm,
					काष्ठा list_head *list,
				       	u8 dead_node)
अणु
	काष्ठा dlm_lock_resource *res, *next;
	काष्ठा dlm_lock *lock;

	spin_lock(&dlm->spinlock);
	list_क्रम_each_entry_safe(res, next, &dlm->reco.resources, recovering) अणु
		/* always prune any $RECOVERY entries क्रम dead nodes,
		 * otherwise hangs can occur during later recovery */
		अगर (dlm_is_recovery_lock(res->lockname.name,
					 res->lockname.len)) अणु
			spin_lock(&res->spinlock);
			list_क्रम_each_entry(lock, &res->granted, list) अणु
				अगर (lock->ml.node == dead_node) अणु
					mlog(0, "AHA! there was "
					     "a $RECOVERY lock for dead "
					     "node %u (%s)!\n",
					     dead_node, dlm->name);
					list_del_init(&lock->list);
					dlm_lock_put(lock);
					/* Can't schedule DLM_UNLOCK_FREE_LOCK
					 * - करो manually */
					dlm_lock_put(lock);
					अवरोध;
				पूर्ण
			पूर्ण
			spin_unlock(&res->spinlock);
			जारी;
		पूर्ण

		अगर (res->owner == dead_node) अणु
			mlog(0, "found lockres owned by dead node while "
				  "doing recovery for node %u. sending it.\n",
				  dead_node);
			list_move_tail(&res->recovering, list);
		पूर्ण अन्यथा अगर (res->owner == DLM_LOCK_RES_OWNER_UNKNOWN) अणु
			mlog(0, "found UNKNOWN owner while doing recovery "
				  "for node %u. sending it.\n", dead_node);
			list_move_tail(&res->recovering, list);
		पूर्ण
	पूर्ण
	spin_unlock(&dlm->spinlock);
पूर्ण

अटल अंतरभूत पूर्णांक dlm_num_locks_in_lockres(काष्ठा dlm_lock_resource *res)
अणु
	पूर्णांक total_locks = 0;
	काष्ठा list_head *iter, *queue = &res->granted;
	पूर्णांक i;

	क्रम (i=0; i<3; i++) अणु
		list_क्रम_each(iter, queue)
			total_locks++;
		queue++;
	पूर्ण
	वापस total_locks;
पूर्ण


अटल पूर्णांक dlm_send_mig_lockres_msg(काष्ठा dlm_ctxt *dlm,
				      काष्ठा dlm_migratable_lockres *mres,
				      u8 send_to,
				      काष्ठा dlm_lock_resource *res,
				      पूर्णांक total_locks)
अणु
	u64 mig_cookie = be64_to_cpu(mres->mig_cookie);
	पूर्णांक mres_total_locks = be32_to_cpu(mres->total_locks);
	पूर्णांक ret = 0, status = 0;
	u8 orig_flags = mres->flags,
	   orig_master = mres->master;

	BUG_ON(mres->num_locks > DLM_MAX_MIGRATABLE_LOCKS);
	अगर (!mres->num_locks)
		वापस 0;

	/* add an all-करोne flag अगर we reached the last lock */
	orig_flags = mres->flags;
	BUG_ON(total_locks > mres_total_locks);
	अगर (total_locks == mres_total_locks)
		mres->flags |= DLM_MRES_ALL_DONE;

	mlog(0, "%s:%.*s: sending mig lockres (%s) to %u\n",
	     dlm->name, res->lockname.len, res->lockname.name,
	     orig_flags & DLM_MRES_MIGRATION ? "migration" : "recovery",
	     send_to);

	/* send it */
	ret = o2net_send_message(DLM_MIG_LOCKRES_MSG, dlm->key, mres,
				 काष्ठा_size(mres, ml, mres->num_locks),
				 send_to, &status);
	अगर (ret < 0) अणु
		/* XXX: negative status is not handled.
		 * this will end up समाप्तing this node. */
		mlog(ML_ERROR, "%s: res %.*s, Error %d send MIG_LOCKRES to "
		     "node %u (%s)\n", dlm->name, mres->lockname_len,
		     mres->lockname, ret, send_to,
		     (orig_flags & DLM_MRES_MIGRATION ?
		      "migration" : "recovery"));
	पूर्ण अन्यथा अणु
		/* might get an -ENOMEM back here */
		ret = status;
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);

			अगर (ret == -EFAULT) अणु
				mlog(ML_ERROR, "node %u told me to kill "
				     "myself!\n", send_to);
				BUG();
			पूर्ण
		पूर्ण
	पूर्ण

	/* zero and reinit the message buffer */
	dlm_init_migratable_lockres(mres, res->lockname.name,
				    res->lockname.len, mres_total_locks,
				    mig_cookie, orig_flags, orig_master);
	वापस ret;
पूर्ण

अटल व्योम dlm_init_migratable_lockres(काष्ठा dlm_migratable_lockres *mres,
					स्थिर अक्षर *lockname, पूर्णांक namelen,
					पूर्णांक total_locks, u64 cookie,
					u8 flags, u8 master)
अणु
	/* mres here is one full page */
	clear_page(mres);
	mres->lockname_len = namelen;
	स_नकल(mres->lockname, lockname, namelen);
	mres->num_locks = 0;
	mres->total_locks = cpu_to_be32(total_locks);
	mres->mig_cookie = cpu_to_be64(cookie);
	mres->flags = flags;
	mres->master = master;
पूर्ण

अटल व्योम dlm_prepare_lvb_क्रम_migration(काष्ठा dlm_lock *lock,
					  काष्ठा dlm_migratable_lockres *mres,
					  पूर्णांक queue)
अणु
	अगर (!lock->lksb)
	       वापस;

	/* Ignore lvb in all locks in the blocked list */
	अगर (queue == DLM_BLOCKED_LIST)
		वापस;

	/* Only consider lvbs in locks with granted EX or PR lock levels */
	अगर (lock->ml.type != LKM_EXMODE && lock->ml.type != LKM_PRMODE)
		वापस;

	अगर (dlm_lvb_is_empty(mres->lvb)) अणु
		स_नकल(mres->lvb, lock->lksb->lvb, DLM_LVB_LEN);
		वापस;
	पूर्ण

	/* Ensure the lvb copied क्रम migration matches in other valid locks */
	अगर (!स_भेद(mres->lvb, lock->lksb->lvb, DLM_LVB_LEN))
		वापस;

	mlog(ML_ERROR, "Mismatched lvb in lock cookie=%u:%llu, name=%.*s, "
	     "node=%u\n",
	     dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
	     dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)),
	     lock->lockres->lockname.len, lock->lockres->lockname.name,
	     lock->ml.node);
	dlm_prपूर्णांक_one_lock_resource(lock->lockres);
	BUG();
पूर्ण

/* वापसs 1 अगर this lock fills the network काष्ठाure,
 * 0 otherwise */
अटल पूर्णांक dlm_add_lock_to_array(काष्ठा dlm_lock *lock,
				 काष्ठा dlm_migratable_lockres *mres, पूर्णांक queue)
अणु
	काष्ठा dlm_migratable_lock *ml;
	पूर्णांक lock_num = mres->num_locks;

	ml = &(mres->ml[lock_num]);
	ml->cookie = lock->ml.cookie;
	ml->type = lock->ml.type;
	ml->convert_type = lock->ml.convert_type;
	ml->highest_blocked = lock->ml.highest_blocked;
	ml->list = queue;
	अगर (lock->lksb) अणु
		ml->flags = lock->lksb->flags;
		dlm_prepare_lvb_क्रम_migration(lock, mres, queue);
	पूर्ण
	ml->node = lock->ml.node;
	mres->num_locks++;
	/* we reached the max, send this network message */
	अगर (mres->num_locks == DLM_MAX_MIGRATABLE_LOCKS)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम dlm_add_dummy_lock(काष्ठा dlm_ctxt *dlm,
			       काष्ठा dlm_migratable_lockres *mres)
अणु
	काष्ठा dlm_lock dummy;
	स_रखो(&dummy, 0, माप(dummy));
	dummy.ml.cookie = 0;
	dummy.ml.type = LKM_IVMODE;
	dummy.ml.convert_type = LKM_IVMODE;
	dummy.ml.highest_blocked = LKM_IVMODE;
	dummy.lksb = शून्य;
	dummy.ml.node = dlm->node_num;
	dlm_add_lock_to_array(&dummy, mres, DLM_BLOCKED_LIST);
पूर्ण

अटल अंतरभूत पूर्णांक dlm_is_dummy_lock(काष्ठा dlm_ctxt *dlm,
				    काष्ठा dlm_migratable_lock *ml,
				    u8 *nodक्रमागत)
अणु
	अगर (unlikely(ml->cookie == 0 &&
	    ml->type == LKM_IVMODE &&
	    ml->convert_type == LKM_IVMODE &&
	    ml->highest_blocked == LKM_IVMODE &&
	    ml->list == DLM_BLOCKED_LIST)) अणु
		*nodक्रमागत = ml->node;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक dlm_send_one_lockres(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock_resource *res,
			 काष्ठा dlm_migratable_lockres *mres,
			 u8 send_to, u8 flags)
अणु
	काष्ठा list_head *queue;
	पूर्णांक total_locks, i;
	u64 mig_cookie = 0;
	काष्ठा dlm_lock *lock;
	पूर्णांक ret = 0;

	BUG_ON(!(flags & (DLM_MRES_RECOVERY|DLM_MRES_MIGRATION)));

	mlog(0, "sending to %u\n", send_to);

	total_locks = dlm_num_locks_in_lockres(res);
	अगर (total_locks > DLM_MAX_MIGRATABLE_LOCKS) अणु
		/* rare, but possible */
		mlog(0, "argh.  lockres has %d locks.  this will "
			  "require more than one network packet to "
			  "migrate\n", total_locks);
		mig_cookie = dlm_get_next_mig_cookie();
	पूर्ण

	dlm_init_migratable_lockres(mres, res->lockname.name,
				    res->lockname.len, total_locks,
				    mig_cookie, flags, res->owner);

	total_locks = 0;
	क्रम (i=DLM_GRANTED_LIST; i<=DLM_BLOCKED_LIST; i++) अणु
		queue = dlm_list_idx_to_ptr(res, i);
		list_क्रम_each_entry(lock, queue, list) अणु
			/* add another lock. */
			total_locks++;
			अगर (!dlm_add_lock_to_array(lock, mres, i))
				जारी;

			/* this filled the lock message,
			 * we must send it immediately. */
			ret = dlm_send_mig_lockres_msg(dlm, mres, send_to,
						       res, total_locks);
			अगर (ret < 0)
				जाओ error;
		पूर्ण
	पूर्ण
	अगर (total_locks == 0) अणु
		/* send a dummy lock to indicate a mastery reference only */
		mlog(0, "%s:%.*s: sending dummy lock to %u, %s\n",
		     dlm->name, res->lockname.len, res->lockname.name,
		     send_to, flags & DLM_MRES_RECOVERY ? "recovery" :
		     "migration");
		dlm_add_dummy_lock(dlm, mres);
	पूर्ण
	/* flush any reमुख्यing locks */
	ret = dlm_send_mig_lockres_msg(dlm, mres, send_to, res, total_locks);
	अगर (ret < 0)
		जाओ error;
	वापस ret;

error:
	mlog(ML_ERROR, "%s: dlm_send_mig_lockres_msg returned %d\n",
	     dlm->name, ret);
	अगर (!dlm_is_host_करोwn(ret))
		BUG();
	mlog(0, "%s: node %u went down while sending %s "
	     "lockres %.*s\n", dlm->name, send_to,
	     flags & DLM_MRES_RECOVERY ?  "recovery" : "migration",
	     res->lockname.len, res->lockname.name);
	वापस ret;
पूर्ण



/*
 * this message will contain no more than one page worth of
 * recovery data, and it will work on only one lockres.
 * there may be many locks in this page, and we may need to रुको
 * क्रम additional packets to complete all the locks (rare, but
 * possible).
 */
/*
 * NOTE: the allocation error हालs here are scary
 * we really cannot afक्रमd to fail an alloc in recovery
 * करो we spin?  वापसing an error only delays the problem really
 */

पूर्णांक dlm_mig_lockres_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			    व्योम **ret_data)
अणु
	काष्ठा dlm_ctxt *dlm = data;
	काष्ठा dlm_migratable_lockres *mres =
		(काष्ठा dlm_migratable_lockres *)msg->buf;
	पूर्णांक ret = 0;
	u8 real_master;
	u8 extra_refs = 0;
	अक्षर *buf = शून्य;
	काष्ठा dlm_work_item *item = शून्य;
	काष्ठा dlm_lock_resource *res = शून्य;
	अचिन्हित पूर्णांक hash;

	अगर (!dlm_grab(dlm))
		वापस -EINVAL;

	अगर (!dlm_joined(dlm)) अणु
		mlog(ML_ERROR, "Domain %s not joined! "
			  "lockres %.*s, master %u\n",
			  dlm->name, mres->lockname_len,
			  mres->lockname, mres->master);
		dlm_put(dlm);
		वापस -EINVAL;
	पूर्ण

	BUG_ON(!(mres->flags & (DLM_MRES_RECOVERY|DLM_MRES_MIGRATION)));

	real_master = mres->master;
	अगर (real_master == DLM_LOCK_RES_OWNER_UNKNOWN) अणु
		/* cannot migrate a lockres with no master */
		BUG_ON(!(mres->flags & DLM_MRES_RECOVERY));
	पूर्ण

	mlog(0, "%s message received from node %u\n",
		  (mres->flags & DLM_MRES_RECOVERY) ?
		  "recovery" : "migration", mres->master);
	अगर (mres->flags & DLM_MRES_ALL_DONE)
		mlog(0, "all done flag.  all lockres data received!\n");

	ret = -ENOMEM;
	buf = kदो_स्मृति(be16_to_cpu(msg->data_len), GFP_NOFS);
	item = kzalloc(माप(*item), GFP_NOFS);
	अगर (!buf || !item)
		जाओ leave;

	/* lookup the lock to see अगर we have a secondary queue क्रम this
	 * alपढ़ोy...  just add the locks in and this will have its owner
	 * and RECOVERY flag changed when it completes. */
	hash = dlm_lockid_hash(mres->lockname, mres->lockname_len);
	spin_lock(&dlm->spinlock);
	res = __dlm_lookup_lockres_full(dlm, mres->lockname, mres->lockname_len,
			hash);
	अगर (res) अणु
	 	/* this will get a ref on res */
		/* mark it as recovering/migrating and hash it */
		spin_lock(&res->spinlock);
		अगर (res->state & DLM_LOCK_RES_DROPPING_REF) अणु
			mlog(0, "%s: node is attempting to migrate "
				"lockres %.*s, but marked as dropping "
				" ref!\n", dlm->name,
				mres->lockname_len, mres->lockname);
			ret = -EINVAL;
			spin_unlock(&res->spinlock);
			spin_unlock(&dlm->spinlock);
			dlm_lockres_put(res);
			जाओ leave;
		पूर्ण

		अगर (mres->flags & DLM_MRES_RECOVERY) अणु
			res->state |= DLM_LOCK_RES_RECOVERING;
		पूर्ण अन्यथा अणु
			अगर (res->state & DLM_LOCK_RES_MIGRATING) अणु
				/* this is at least the second
				 * lockres message */
				mlog(0, "lock %.*s is already migrating\n",
					  mres->lockname_len,
					  mres->lockname);
			पूर्ण अन्यथा अगर (res->state & DLM_LOCK_RES_RECOVERING) अणु
				/* caller should BUG */
				mlog(ML_ERROR, "node is attempting to migrate "
				     "lock %.*s, but marked as recovering!\n",
				     mres->lockname_len, mres->lockname);
				ret = -EFAULT;
				spin_unlock(&res->spinlock);
				spin_unlock(&dlm->spinlock);
				dlm_lockres_put(res);
				जाओ leave;
			पूर्ण
			res->state |= DLM_LOCK_RES_MIGRATING;
		पूर्ण
		spin_unlock(&res->spinlock);
		spin_unlock(&dlm->spinlock);
	पूर्ण अन्यथा अणु
		spin_unlock(&dlm->spinlock);
		/* need to allocate, just like अगर it was
		 * mastered here normally  */
		res = dlm_new_lockres(dlm, mres->lockname, mres->lockname_len);
		अगर (!res)
			जाओ leave;

		/* to match the ref that we would have gotten अगर
		 * dlm_lookup_lockres had succeeded */
		dlm_lockres_get(res);

		/* mark it as recovering/migrating and hash it */
		अगर (mres->flags & DLM_MRES_RECOVERY)
			res->state |= DLM_LOCK_RES_RECOVERING;
		अन्यथा
			res->state |= DLM_LOCK_RES_MIGRATING;

		spin_lock(&dlm->spinlock);
		__dlm_insert_lockres(dlm, res);
		spin_unlock(&dlm->spinlock);

		/* Add an extra ref क्रम this lock-less lockres lest the
		 * dlm_thपढ़ो purges it beक्रमe we get the chance to add
		 * locks to it */
		dlm_lockres_get(res);

		/* There are three refs that need to be put.
		 * 1. Taken above.
		 * 2. kref_init in dlm_new_lockres()->dlm_init_lockres().
		 * 3. dlm_lookup_lockres()
		 * The first one is handled at the end of this function. The
		 * other two are handled in the worker thपढ़ो after locks have
		 * been attached. Yes, we करोn't रुको क्रम purge समय to match
		 * kref_init. The lockres will still have atleast one ref
		 * added because it is in the hash __dlm_insert_lockres() */
		extra_refs++;

		/* now that the new lockres is inserted,
		 * make it usable by other processes */
		spin_lock(&res->spinlock);
		res->state &= ~DLM_LOCK_RES_IN_PROGRESS;
		spin_unlock(&res->spinlock);
		wake_up(&res->wq);
	पूर्ण

	/* at this poपूर्णांक we have allocated everything we need,
	 * and we have a hashed lockres with an extra ref and
	 * the proper res->state flags. */
	ret = 0;
	spin_lock(&res->spinlock);
	/* drop this either when master requery finds a dअगरferent master
	 * or when a lock is added by the recovery worker */
	dlm_lockres_grab_inflight_ref(dlm, res);
	अगर (mres->master == DLM_LOCK_RES_OWNER_UNKNOWN) अणु
		/* migration cannot have an unknown master */
		BUG_ON(!(mres->flags & DLM_MRES_RECOVERY));
		mlog(0, "recovery has passed me a lockres with an "
			  "unknown owner.. will need to requery: "
			  "%.*s\n", mres->lockname_len, mres->lockname);
	पूर्ण अन्यथा अणु
		/* take a reference now to pin the lockres, drop it
		 * when locks are added in the worker */
		dlm_change_lockres_owner(dlm, res, dlm->node_num);
	पूर्ण
	spin_unlock(&res->spinlock);

	/* queue up work क्रम dlm_mig_lockres_worker */
	dlm_grab(dlm);  /* get an extra ref क्रम the work item */
	स_नकल(buf, msg->buf, be16_to_cpu(msg->data_len));  /* copy the whole message */
	dlm_init_work_item(dlm, item, dlm_mig_lockres_worker, buf);
	item->u.ml.lockres = res; /* alपढ़ोy have a ref */
	item->u.ml.real_master = real_master;
	item->u.ml.extra_ref = extra_refs;
	spin_lock(&dlm->work_lock);
	list_add_tail(&item->list, &dlm->work_list);
	spin_unlock(&dlm->work_lock);
	queue_work(dlm->dlm_worker, &dlm->dispatched_work);

leave:
	/* One extra ref taken needs to be put here */
	अगर (extra_refs)
		dlm_lockres_put(res);

	dlm_put(dlm);
	अगर (ret < 0) अणु
		kमुक्त(buf);
		kमुक्त(item);
		mlog_त्रुटि_सं(ret);
	पूर्ण

	वापस ret;
पूर्ण


अटल व्योम dlm_mig_lockres_worker(काष्ठा dlm_work_item *item, व्योम *data)
अणु
	काष्ठा dlm_ctxt *dlm;
	काष्ठा dlm_migratable_lockres *mres;
	पूर्णांक ret = 0;
	काष्ठा dlm_lock_resource *res;
	u8 real_master;
	u8 extra_ref;

	dlm = item->dlm;
	mres = (काष्ठा dlm_migratable_lockres *)data;

	res = item->u.ml.lockres;
	real_master = item->u.ml.real_master;
	extra_ref = item->u.ml.extra_ref;

	अगर (real_master == DLM_LOCK_RES_OWNER_UNKNOWN) अणु
		/* this हाल is super-rare. only occurs अगर
		 * node death happens during migration. */
again:
		ret = dlm_lockres_master_requery(dlm, res, &real_master);
		अगर (ret < 0) अणु
			mlog(0, "dlm_lockres_master_requery ret=%d\n",
				  ret);
			जाओ again;
		पूर्ण
		अगर (real_master == DLM_LOCK_RES_OWNER_UNKNOWN) अणु
			mlog(0, "lockres %.*s not claimed.  "
				   "this node will take it.\n",
				   res->lockname.len, res->lockname.name);
		पूर्ण अन्यथा अणु
			spin_lock(&res->spinlock);
			dlm_lockres_drop_inflight_ref(dlm, res);
			spin_unlock(&res->spinlock);
			mlog(0, "master needs to respond to sender "
				  "that node %u still owns %.*s\n",
				  real_master, res->lockname.len,
				  res->lockname.name);
			/* cannot touch this lockres */
			जाओ leave;
		पूर्ण
	पूर्ण

	ret = dlm_process_recovery_data(dlm, res, mres);
	अगर (ret < 0)
		mlog(0, "dlm_process_recovery_data returned  %d\n", ret);
	अन्यथा
		mlog(0, "dlm_process_recovery_data succeeded\n");

	अगर ((mres->flags & (DLM_MRES_MIGRATION|DLM_MRES_ALL_DONE)) ==
	                   (DLM_MRES_MIGRATION|DLM_MRES_ALL_DONE)) अणु
		ret = dlm_finish_migration(dlm, res, mres->master);
		अगर (ret < 0)
			mlog_त्रुटि_सं(ret);
	पूर्ण

leave:
	/* See comment in dlm_mig_lockres_handler() */
	अगर (res) अणु
		अगर (extra_ref)
			dlm_lockres_put(res);
		dlm_lockres_put(res);
	पूर्ण
	kमुक्त(data);
पूर्ण



अटल पूर्णांक dlm_lockres_master_requery(काष्ठा dlm_ctxt *dlm,
				      काष्ठा dlm_lock_resource *res,
				      u8 *real_master)
अणु
	काष्ठा dlm_node_iter iter;
	पूर्णांक nodक्रमागत;
	पूर्णांक ret = 0;

	*real_master = DLM_LOCK_RES_OWNER_UNKNOWN;

	/* we only reach here अगर one of the two nodes in a
	 * migration died जबतक the migration was in progress.
	 * at this poपूर्णांक we need to requery the master.  we
	 * know that the new_master got as far as creating
	 * an mle on at least one node, but we करो not know
	 * अगर any nodes had actually cleared the mle and set
	 * the master to the new_master.  the old master
	 * is supposed to set the owner to UNKNOWN in the
	 * event of a new_master death, so the only possible
	 * responses that we can get from nodes here are
	 * that the master is new_master, or that the master
	 * is UNKNOWN.
	 * अगर all nodes come back with UNKNOWN then we know
	 * the lock needs remastering here.
	 * अगर any node comes back with a valid master, check
	 * to see अगर that master is the one that we are
	 * recovering.  अगर so, then the new_master died and
	 * we need to remaster this lock.  अगर not, then the
	 * new_master survived and that node will respond to
	 * other nodes about the owner.
	 * अगर there is an owner, this node needs to dump this
	 * lockres and alert the sender that this lockres
	 * was rejected. */
	spin_lock(&dlm->spinlock);
	dlm_node_iter_init(dlm->करोमुख्य_map, &iter);
	spin_unlock(&dlm->spinlock);

	जबतक ((nodक्रमागत = dlm_node_iter_next(&iter)) >= 0) अणु
		/* करो not send to self */
		अगर (nodक्रमागत == dlm->node_num)
			जारी;
		ret = dlm_करो_master_requery(dlm, res, nodक्रमागत, real_master);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			अगर (!dlm_is_host_करोwn(ret))
				BUG();
			/* host is करोwn, so answer क्रम that node would be
			 * DLM_LOCK_RES_OWNER_UNKNOWN.  जारी. */
		पूर्ण
		अगर (*real_master != DLM_LOCK_RES_OWNER_UNKNOWN) अणु
			mlog(0, "lock master is %u\n", *real_master);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण


पूर्णांक dlm_करो_master_requery(काष्ठा dlm_ctxt *dlm, काष्ठा dlm_lock_resource *res,
			  u8 nodक्रमागत, u8 *real_master)
अणु
	पूर्णांक ret;
	काष्ठा dlm_master_requery req;
	पूर्णांक status = DLM_LOCK_RES_OWNER_UNKNOWN;

	स_रखो(&req, 0, माप(req));
	req.node_idx = dlm->node_num;
	req.namelen = res->lockname.len;
	स_नकल(req.name, res->lockname.name, res->lockname.len);

resend:
	ret = o2net_send_message(DLM_MASTER_REQUERY_MSG, dlm->key,
				 &req, माप(req), nodक्रमागत, &status);
	अगर (ret < 0)
		mlog(ML_ERROR, "Error %d when sending message %u (key "
		     "0x%x) to node %u\n", ret, DLM_MASTER_REQUERY_MSG,
		     dlm->key, nodक्रमागत);
	अन्यथा अगर (status == -ENOMEM) अणु
		mlog_त्रुटि_सं(status);
		msleep(50);
		जाओ resend;
	पूर्ण अन्यथा अणु
		BUG_ON(status < 0);
		BUG_ON(status > DLM_LOCK_RES_OWNER_UNKNOWN);
		*real_master = (u8) (status & 0xff);
		mlog(0, "node %u responded to master requery with %u\n",
			  nodक्रमागत, *real_master);
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण


/* this function cannot error, so unless the sending
 * or receiving of the message failed, the owner can
 * be trusted */
पूर्णांक dlm_master_requery_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			       व्योम **ret_data)
अणु
	काष्ठा dlm_ctxt *dlm = data;
	काष्ठा dlm_master_requery *req = (काष्ठा dlm_master_requery *)msg->buf;
	काष्ठा dlm_lock_resource *res = शून्य;
	अचिन्हित पूर्णांक hash;
	पूर्णांक master = DLM_LOCK_RES_OWNER_UNKNOWN;
	u32 flags = DLM_ASSERT_MASTER_REQUERY;
	पूर्णांक dispatched = 0;

	अगर (!dlm_grab(dlm)) अणु
		/* since the करोमुख्य has gone away on this
		 * node, the proper response is UNKNOWN */
		वापस master;
	पूर्ण

	hash = dlm_lockid_hash(req->name, req->namelen);

	spin_lock(&dlm->spinlock);
	res = __dlm_lookup_lockres(dlm, req->name, req->namelen, hash);
	अगर (res) अणु
		spin_lock(&res->spinlock);
		master = res->owner;
		अगर (master == dlm->node_num) अणु
			पूर्णांक ret = dlm_dispatch_निश्चित_master(dlm, res,
							     0, 0, flags);
			अगर (ret < 0) अणु
				mlog_त्रुटि_सं(ret);
				spin_unlock(&res->spinlock);
				dlm_lockres_put(res);
				spin_unlock(&dlm->spinlock);
				dlm_put(dlm);
				/* sender will take care of this and retry */
				वापस ret;
			पूर्ण अन्यथा अणु
				dispatched = 1;
				__dlm_lockres_grab_inflight_worker(dlm, res);
				spin_unlock(&res->spinlock);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* put.. inहाल we are not the master */
			spin_unlock(&res->spinlock);
			dlm_lockres_put(res);
		पूर्ण
	पूर्ण
	spin_unlock(&dlm->spinlock);

	अगर (!dispatched)
		dlm_put(dlm);
	वापस master;
पूर्ण

अटल अंतरभूत काष्ठा list_head *
dlm_list_num_to_poपूर्णांकer(काष्ठा dlm_lock_resource *res, पूर्णांक list_num)
अणु
	काष्ठा list_head *ret;
	BUG_ON(list_num < 0);
	BUG_ON(list_num > 2);
	ret = &(res->granted);
	ret += list_num;
	वापस ret;
पूर्ण
/* TODO: करो ast flush business
 * TODO: करो MIGRATING and RECOVERING spinning
 */

/*
* NOTE about in-flight requests during migration:
*
* Beक्रमe attempting the migrate, the master has marked the lockres as
* MIGRATING and then flushed all of its pending ASTS.  So any in-flight
* requests either got queued beक्रमe the MIGRATING flag got set, in which
* हाल the lock data will reflect the change and a वापस message is on
* the way, or the request failed to get in beक्रमe MIGRATING got set.  In
* this हाल, the caller will be told to spin and रुको क्रम the MIGRATING
* flag to be dropped, then recheck the master.
* This holds true क्रम the convert, cancel and unlock हालs, and since lvb
* updates are tied to these same messages, it applies to lvb updates as
* well.  For the lock हाल, there is no way a lock can be on the master
* queue and not be on the secondary queue since the lock is always added
* locally first.  This means that the new target node will never be sent
* a lock that he करोesn't alपढ़ोy have on the list.
* In total, this means that the local lock is correct and should not be
* updated to match the one sent by the master.  Any messages sent back
* from the master beक्रमe the MIGRATING flag will bring the lock properly
* up-to-date, and the change will be ordered properly क्रम the रुकोer.
* We will *not* attempt to modअगरy the lock underneath the रुकोer.
*/

अटल पूर्णांक dlm_process_recovery_data(काष्ठा dlm_ctxt *dlm,
				     काष्ठा dlm_lock_resource *res,
				     काष्ठा dlm_migratable_lockres *mres)
अणु
	काष्ठा dlm_migratable_lock *ml;
	काष्ठा list_head *queue, *iter;
	काष्ठा list_head *पंचांगpq = शून्य;
	काष्ठा dlm_lock *newlock = शून्य;
	काष्ठा dlm_lockstatus *lksb = शून्य;
	पूर्णांक ret = 0;
	पूर्णांक i, j, bad;
	काष्ठा dlm_lock *lock;
	u8 from = O2NM_MAX_NODES;
	__be64 c;

	mlog(0, "running %d locks for this lockres\n", mres->num_locks);
	क्रम (i=0; i<mres->num_locks; i++) अणु
		ml = &(mres->ml[i]);

		अगर (dlm_is_dummy_lock(dlm, ml, &from)) अणु
			/* placeholder, just need to set the refmap bit */
			BUG_ON(mres->num_locks != 1);
			mlog(0, "%s:%.*s: dummy lock for %u\n",
			     dlm->name, mres->lockname_len, mres->lockname,
			     from);
			spin_lock(&res->spinlock);
			dlm_lockres_set_refmap_bit(dlm, res, from);
			spin_unlock(&res->spinlock);
			अवरोध;
		पूर्ण
		BUG_ON(ml->highest_blocked != LKM_IVMODE);
		newlock = शून्य;
		lksb = शून्य;

		queue = dlm_list_num_to_poपूर्णांकer(res, ml->list);
		पंचांगpq = शून्य;

		/* अगर the lock is क्रम the local node it needs to
		 * be moved to the proper location within the queue.
		 * करो not allocate a new lock काष्ठाure. */
		अगर (ml->node == dlm->node_num) अणु
			/* MIGRATION ONLY! */
			BUG_ON(!(mres->flags & DLM_MRES_MIGRATION));

			lock = शून्य;
			spin_lock(&res->spinlock);
			क्रम (j = DLM_GRANTED_LIST; j <= DLM_BLOCKED_LIST; j++) अणु
				पंचांगpq = dlm_list_idx_to_ptr(res, j);
				list_क्रम_each(iter, पंचांगpq) अणु
					lock = list_entry(iter,
						  काष्ठा dlm_lock, list);
					अगर (lock->ml.cookie == ml->cookie)
						अवरोध;
					lock = शून्य;
				पूर्ण
				अगर (lock)
					अवरोध;
			पूर्ण

			/* lock is always created locally first, and
			 * destroyed locally last.  it must be on the list */
			अगर (!lock) अणु
				c = ml->cookie;
				mlog(ML_ERROR, "Could not find local lock "
					       "with cookie %u:%llu, node %u, "
					       "list %u, flags 0x%x, type %d, "
					       "conv %d, highest blocked %d\n",
				     dlm_get_lock_cookie_node(be64_to_cpu(c)),
				     dlm_get_lock_cookie_seq(be64_to_cpu(c)),
				     ml->node, ml->list, ml->flags, ml->type,
				     ml->convert_type, ml->highest_blocked);
				__dlm_prपूर्णांक_one_lock_resource(res);
				BUG();
			पूर्ण

			अगर (lock->ml.node != ml->node) अणु
				c = lock->ml.cookie;
				mlog(ML_ERROR, "Mismatched node# in lock "
				     "cookie %u:%llu, name %.*s, node %u\n",
				     dlm_get_lock_cookie_node(be64_to_cpu(c)),
				     dlm_get_lock_cookie_seq(be64_to_cpu(c)),
				     res->lockname.len, res->lockname.name,
				     lock->ml.node);
				c = ml->cookie;
				mlog(ML_ERROR, "Migrate lock cookie %u:%llu, "
				     "node %u, list %u, flags 0x%x, type %d, "
				     "conv %d, highest blocked %d\n",
				     dlm_get_lock_cookie_node(be64_to_cpu(c)),
				     dlm_get_lock_cookie_seq(be64_to_cpu(c)),
				     ml->node, ml->list, ml->flags, ml->type,
				     ml->convert_type, ml->highest_blocked);
				__dlm_prपूर्णांक_one_lock_resource(res);
				BUG();
			पूर्ण

			अगर (पंचांगpq != queue) अणु
				c = ml->cookie;
				mlog(0, "Lock cookie %u:%llu was on list %u "
				     "instead of list %u for %.*s\n",
				     dlm_get_lock_cookie_node(be64_to_cpu(c)),
				     dlm_get_lock_cookie_seq(be64_to_cpu(c)),
				     j, ml->list, res->lockname.len,
				     res->lockname.name);
				__dlm_prपूर्णांक_one_lock_resource(res);
				spin_unlock(&res->spinlock);
				जारी;
			पूर्ण

			/* see NOTE above about why we करो not update
			 * to match the master here */

			/* move the lock to its proper place */
			/* करो not alter lock refcount.  चयनing lists. */
			list_move_tail(&lock->list, queue);
			spin_unlock(&res->spinlock);

			mlog(0, "just reordered a local lock!\n");
			जारी;
		पूर्ण

		/* lock is क्रम another node. */
		newlock = dlm_new_lock(ml->type, ml->node,
				       be64_to_cpu(ml->cookie), शून्य);
		अगर (!newlock) अणु
			ret = -ENOMEM;
			जाओ leave;
		पूर्ण
		lksb = newlock->lksb;
		dlm_lock_attach_lockres(newlock, res);

		अगर (ml->convert_type != LKM_IVMODE) अणु
			BUG_ON(queue != &res->converting);
			newlock->ml.convert_type = ml->convert_type;
		पूर्ण
		lksb->flags |= (ml->flags &
				(DLM_LKSB_PUT_LVB|DLM_LKSB_GET_LVB));

		अगर (ml->type == LKM_NLMODE)
			जाओ skip_lvb;

		/*
		 * If the lock is in the blocked list it can't have a valid lvb,
		 * so skip it
		 */
		अगर (ml->list == DLM_BLOCKED_LIST)
			जाओ skip_lvb;

		अगर (!dlm_lvb_is_empty(mres->lvb)) अणु
			अगर (lksb->flags & DLM_LKSB_PUT_LVB) अणु
				/* other node was trying to update
				 * lvb when node died.  recreate the
				 * lksb with the updated lvb. */
				स_नकल(lksb->lvb, mres->lvb, DLM_LVB_LEN);
				/* the lock resource lvb update must happen
				 * NOW, beक्रमe the spinlock is dropped.
				 * we no दीर्घer रुको क्रम the AST to update
				 * the lvb. */
				स_नकल(res->lvb, mres->lvb, DLM_LVB_LEN);
			पूर्ण अन्यथा अणु
				/* otherwise, the node is sending its
				 * most recent valid lvb info */
				BUG_ON(ml->type != LKM_EXMODE &&
				       ml->type != LKM_PRMODE);
				अगर (!dlm_lvb_is_empty(res->lvb) &&
 				    (ml->type == LKM_EXMODE ||
 				     स_भेद(res->lvb, mres->lvb, DLM_LVB_LEN))) अणु
 					पूर्णांक i;
 					mlog(ML_ERROR, "%s:%.*s: received bad "
 					     "lvb! type=%d\n", dlm->name,
 					     res->lockname.len,
 					     res->lockname.name, ml->type);
 					prपूर्णांकk("lockres lvb=[");
 					क्रम (i=0; i<DLM_LVB_LEN; i++)
 						prपूर्णांकk("%02x", res->lvb[i]);
 					prपूर्णांकk("]\nmigrated lvb=[");
 					क्रम (i=0; i<DLM_LVB_LEN; i++)
 						prपूर्णांकk("%02x", mres->lvb[i]);
 					prपूर्णांकk("]\n");
 					dlm_prपूर्णांक_one_lock_resource(res);
 					BUG();
				पूर्ण
				स_नकल(res->lvb, mres->lvb, DLM_LVB_LEN);
			पूर्ण
		पूर्ण
skip_lvb:

		/* NOTE:
		 * wrt lock queue ordering and recovery:
		 *    1. order of locks on granted queue is
		 *       meaningless.
		 *    2. order of locks on converting queue is
		 *       LOST with the node death.  sorry अक्षरlie.
		 *    3. order of locks on the blocked queue is
		 *       also LOST.
		 * order of locks करोes not affect पूर्णांकegrity, it
		 * just means that a lock request may get pushed
		 * back in line as a result of the node death.
		 * also note that क्रम a given node the lock order
		 * क्रम its secondary queue locks is preserved
		 * relative to each other, but clearly *not*
		 * preserved relative to locks from other nodes.
		 */
		bad = 0;
		spin_lock(&res->spinlock);
		list_क्रम_each_entry(lock, queue, list) अणु
			अगर (lock->ml.cookie == ml->cookie) अणु
				c = lock->ml.cookie;
				mlog(ML_ERROR, "%s:%.*s: %u:%llu: lock already "
				     "exists on this lockres!\n", dlm->name,
				     res->lockname.len, res->lockname.name,
				     dlm_get_lock_cookie_node(be64_to_cpu(c)),
				     dlm_get_lock_cookie_seq(be64_to_cpu(c)));

				mlog(ML_NOTICE, "sent lock: type=%d, conv=%d, "
				     "node=%u, cookie=%u:%llu, queue=%d\n",
	      			     ml->type, ml->convert_type, ml->node,
				     dlm_get_lock_cookie_node(be64_to_cpu(ml->cookie)),
				     dlm_get_lock_cookie_seq(be64_to_cpu(ml->cookie)),
				     ml->list);

				__dlm_prपूर्णांक_one_lock_resource(res);
				bad = 1;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!bad) अणु
			dlm_lock_get(newlock);
			अगर (mres->flags & DLM_MRES_RECOVERY &&
					ml->list == DLM_CONVERTING_LIST &&
					newlock->ml.type >
					newlock->ml.convert_type) अणु
				/* newlock is करोing करोwnconvert, add it to the
				 * head of converting list */
				list_add(&newlock->list, queue);
			पूर्ण अन्यथा
				list_add_tail(&newlock->list, queue);
			mlog(0, "%s:%.*s: added lock for node %u, "
			     "setting refmap bit\n", dlm->name,
			     res->lockname.len, res->lockname.name, ml->node);
			dlm_lockres_set_refmap_bit(dlm, res, ml->node);
		पूर्ण
		spin_unlock(&res->spinlock);
	पूर्ण
	mlog(0, "done running all the locks\n");

leave:
	/* balance the ref taken when the work was queued */
	spin_lock(&res->spinlock);
	dlm_lockres_drop_inflight_ref(dlm, res);
	spin_unlock(&res->spinlock);

	अगर (ret < 0)
		mlog_त्रुटि_सं(ret);

	वापस ret;
पूर्ण

व्योम dlm_move_lockres_to_recovery_list(काष्ठा dlm_ctxt *dlm,
				       काष्ठा dlm_lock_resource *res)
अणु
	पूर्णांक i;
	काष्ठा list_head *queue;
	काष्ठा dlm_lock *lock, *next;

	निश्चित_spin_locked(&dlm->spinlock);
	निश्चित_spin_locked(&res->spinlock);
	res->state |= DLM_LOCK_RES_RECOVERING;
	अगर (!list_empty(&res->recovering)) अणु
		mlog(0,
		     "Recovering res %s:%.*s, is already on recovery list!\n",
		     dlm->name, res->lockname.len, res->lockname.name);
		list_del_init(&res->recovering);
		dlm_lockres_put(res);
	पूर्ण
	/* We need to hold a reference जबतक on the recovery list */
	dlm_lockres_get(res);
	list_add_tail(&res->recovering, &dlm->reco.resources);

	/* find any pending locks and put them back on proper list */
	क्रम (i=DLM_BLOCKED_LIST; i>=DLM_GRANTED_LIST; i--) अणु
		queue = dlm_list_idx_to_ptr(res, i);
		list_क्रम_each_entry_safe(lock, next, queue, list) अणु
			dlm_lock_get(lock);
			अगर (lock->convert_pending) अणु
				/* move converting lock back to granted */
				mlog(0, "node died with convert pending "
				     "on %.*s. move back to granted list.\n",
				     res->lockname.len, res->lockname.name);
				dlm_revert_pending_convert(res, lock);
				lock->convert_pending = 0;
			पूर्ण अन्यथा अगर (lock->lock_pending) अणु
				/* हटाओ pending lock requests completely */
				BUG_ON(i != DLM_BLOCKED_LIST);
				mlog(0, "node died with lock pending "
				     "on %.*s. remove from blocked list and skip.\n",
				     res->lockname.len, res->lockname.name);
				/* lock will be भग्नing until ref in
				 * dlmlock_remote is मुक्तd after the network
				 * call वापसs.  ok क्रम it to not be on any
				 * list since no ast can be called
				 * (the master is dead). */
				dlm_revert_pending_lock(res, lock);
				lock->lock_pending = 0;
			पूर्ण अन्यथा अगर (lock->unlock_pending) अणु
				/* अगर an unlock was in progress, treat as
				 * अगर this had completed successfully
				 * beक्रमe sending this lock state to the
				 * new master.  note that the dlm_unlock
				 * call is still responsible क्रम calling
				 * the unlockast.  that will happen after
				 * the network call बार out.  क्रम now,
				 * just move lists to prepare the new
				 * recovery master.  */
				BUG_ON(i != DLM_GRANTED_LIST);
				mlog(0, "node died with unlock pending "
				     "on %.*s. remove from blocked list and skip.\n",
				     res->lockname.len, res->lockname.name);
				dlm_commit_pending_unlock(res, lock);
				lock->unlock_pending = 0;
			पूर्ण अन्यथा अगर (lock->cancel_pending) अणु
				/* अगर a cancel was in progress, treat as
				 * अगर this had completed successfully
				 * beक्रमe sending this lock state to the
				 * new master */
				BUG_ON(i != DLM_CONVERTING_LIST);
				mlog(0, "node died with cancel pending "
				     "on %.*s. move back to granted list.\n",
				     res->lockname.len, res->lockname.name);
				dlm_commit_pending_cancel(res, lock);
				lock->cancel_pending = 0;
			पूर्ण
			dlm_lock_put(lock);
		पूर्ण
	पूर्ण
पूर्ण



/* हटाओs all recovered locks from the recovery list.
 * sets the res->owner to the new master.
 * unsets the RECOVERY flag and wakes रुकोers. */
अटल व्योम dlm_finish_local_lockres_recovery(काष्ठा dlm_ctxt *dlm,
					      u8 dead_node, u8 new_master)
अणु
	पूर्णांक i;
	काष्ठा hlist_head *bucket;
	काष्ठा dlm_lock_resource *res, *next;

	निश्चित_spin_locked(&dlm->spinlock);

	list_क्रम_each_entry_safe(res, next, &dlm->reco.resources, recovering) अणु
		अगर (res->owner == dead_node) अणु
			mlog(0, "%s: res %.*s, Changing owner from %u to %u\n",
			     dlm->name, res->lockname.len, res->lockname.name,
			     res->owner, new_master);
			list_del_init(&res->recovering);
			spin_lock(&res->spinlock);
			/* new_master has our reference from
			 * the lock state sent during recovery */
			dlm_change_lockres_owner(dlm, res, new_master);
			res->state &= ~DLM_LOCK_RES_RECOVERING;
			अगर (__dlm_lockres_has_locks(res))
				__dlm_dirty_lockres(dlm, res);
			spin_unlock(&res->spinlock);
			wake_up(&res->wq);
			dlm_lockres_put(res);
		पूर्ण
	पूर्ण

	/* this will become unnecessary eventually, but
	 * क्रम now we need to run the whole hash, clear
	 * the RECOVERING state and set the owner
	 * अगर necessary */
	क्रम (i = 0; i < DLM_HASH_BUCKETS; i++) अणु
		bucket = dlm_lockres_hash(dlm, i);
		hlist_क्रम_each_entry(res, bucket, hash_node) अणु
			अगर (res->state & DLM_LOCK_RES_RECOVERY_WAITING) अणु
				spin_lock(&res->spinlock);
				res->state &= ~DLM_LOCK_RES_RECOVERY_WAITING;
				spin_unlock(&res->spinlock);
				wake_up(&res->wq);
			पूर्ण

			अगर (!(res->state & DLM_LOCK_RES_RECOVERING))
				जारी;

			अगर (res->owner != dead_node &&
			    res->owner != dlm->node_num)
				जारी;

			अगर (!list_empty(&res->recovering)) अणु
				list_del_init(&res->recovering);
				dlm_lockres_put(res);
			पूर्ण

			/* new_master has our reference from
			 * the lock state sent during recovery */
			mlog(0, "%s: res %.*s, Changing owner from %u to %u\n",
			     dlm->name, res->lockname.len, res->lockname.name,
			     res->owner, new_master);
			spin_lock(&res->spinlock);
			dlm_change_lockres_owner(dlm, res, new_master);
			res->state &= ~DLM_LOCK_RES_RECOVERING;
			अगर (__dlm_lockres_has_locks(res))
				__dlm_dirty_lockres(dlm, res);
			spin_unlock(&res->spinlock);
			wake_up(&res->wq);
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक dlm_lvb_needs_invalidation(काष्ठा dlm_lock *lock, पूर्णांक local)
अणु
	अगर (local) अणु
		अगर (lock->ml.type != LKM_EXMODE &&
		    lock->ml.type != LKM_PRMODE)
			वापस 1;
	पूर्ण अन्यथा अगर (lock->ml.type == LKM_EXMODE)
		वापस 1;
	वापस 0;
पूर्ण

अटल व्योम dlm_revalidate_lvb(काष्ठा dlm_ctxt *dlm,
			       काष्ठा dlm_lock_resource *res, u8 dead_node)
अणु
	काष्ठा list_head *queue;
	काष्ठा dlm_lock *lock;
	पूर्णांक blank_lvb = 0, local = 0;
	पूर्णांक i;
	u8 search_node;

	निश्चित_spin_locked(&dlm->spinlock);
	निश्चित_spin_locked(&res->spinlock);

	अगर (res->owner == dlm->node_num)
		/* अगर this node owned the lockres, and अगर the dead node
		 * had an EX when he died, blank out the lvb */
		search_node = dead_node;
	अन्यथा अणु
		/* अगर this is a secondary lockres, and we had no EX or PR
		 * locks granted, we can no दीर्घer trust the lvb */
		search_node = dlm->node_num;
		local = 1;  /* check local state क्रम valid lvb */
	पूर्ण

	क्रम (i=DLM_GRANTED_LIST; i<=DLM_CONVERTING_LIST; i++) अणु
		queue = dlm_list_idx_to_ptr(res, i);
		list_क्रम_each_entry(lock, queue, list) अणु
			अगर (lock->ml.node == search_node) अणु
				अगर (dlm_lvb_needs_invalidation(lock, local)) अणु
					/* zero the lksb lvb and lockres lvb */
					blank_lvb = 1;
					स_रखो(lock->lksb->lvb, 0, DLM_LVB_LEN);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (blank_lvb) अणु
		mlog(0, "clearing %.*s lvb, dead node %u had EX\n",
		     res->lockname.len, res->lockname.name, dead_node);
		स_रखो(res->lvb, 0, DLM_LVB_LEN);
	पूर्ण
पूर्ण

अटल व्योम dlm_मुक्त_dead_locks(काष्ठा dlm_ctxt *dlm,
				काष्ठा dlm_lock_resource *res, u8 dead_node)
अणु
	काष्ठा dlm_lock *lock, *next;
	अचिन्हित पूर्णांक मुक्तd = 0;

	/* this node is the lockres master:
	 * 1) हटाओ any stale locks क्रम the dead node
	 * 2) अगर the dead node had an EX when he died, blank out the lvb
	 */
	निश्चित_spin_locked(&dlm->spinlock);
	निश्चित_spin_locked(&res->spinlock);

	/* We करो two dlm_lock_put(). One क्रम removing from list and the other is
	 * to क्रमce the DLM_UNLOCK_FREE_LOCK action so as to मुक्त the locks */

	/* TODO: check pending_asts, pending_basts here */
	list_क्रम_each_entry_safe(lock, next, &res->granted, list) अणु
		अगर (lock->ml.node == dead_node) अणु
			list_del_init(&lock->list);
			dlm_lock_put(lock);
			/* Can't schedule DLM_UNLOCK_FREE_LOCK - करो manually */
			dlm_lock_put(lock);
			मुक्तd++;
		पूर्ण
	पूर्ण
	list_क्रम_each_entry_safe(lock, next, &res->converting, list) अणु
		अगर (lock->ml.node == dead_node) अणु
			list_del_init(&lock->list);
			dlm_lock_put(lock);
			/* Can't schedule DLM_UNLOCK_FREE_LOCK - करो manually */
			dlm_lock_put(lock);
			मुक्तd++;
		पूर्ण
	पूर्ण
	list_क्रम_each_entry_safe(lock, next, &res->blocked, list) अणु
		अगर (lock->ml.node == dead_node) अणु
			list_del_init(&lock->list);
			dlm_lock_put(lock);
			/* Can't schedule DLM_UNLOCK_FREE_LOCK - करो manually */
			dlm_lock_put(lock);
			मुक्तd++;
		पूर्ण
	पूर्ण

	अगर (मुक्तd) अणु
		mlog(0, "%s:%.*s: freed %u locks for dead node %u, "
		     "dropping ref from lockres\n", dlm->name,
		     res->lockname.len, res->lockname.name, मुक्तd, dead_node);
		अगर(!test_bit(dead_node, res->refmap)) अणु
			mlog(ML_ERROR, "%s:%.*s: freed %u locks for dead node %u, "
			     "but ref was not set\n", dlm->name,
			     res->lockname.len, res->lockname.name, मुक्तd, dead_node);
			__dlm_prपूर्णांक_one_lock_resource(res);
		पूर्ण
		res->state |= DLM_LOCK_RES_RECOVERY_WAITING;
		dlm_lockres_clear_refmap_bit(dlm, res, dead_node);
	पूर्ण अन्यथा अगर (test_bit(dead_node, res->refmap)) अणु
		mlog(0, "%s:%.*s: dead node %u had a ref, but had "
		     "no locks and had not purged before dying\n", dlm->name,
		     res->lockname.len, res->lockname.name, dead_node);
		dlm_lockres_clear_refmap_bit(dlm, res, dead_node);
	पूर्ण

	/* करो not kick thपढ़ो yet */
	__dlm_dirty_lockres(dlm, res);
पूर्ण

अटल व्योम dlm_करो_local_recovery_cleanup(काष्ठा dlm_ctxt *dlm, u8 dead_node)
अणु
	काष्ठा dlm_lock_resource *res;
	पूर्णांक i;
	काष्ठा hlist_head *bucket;
	काष्ठा hlist_node *पंचांगp;
	काष्ठा dlm_lock *lock;


	/* purge any stale mles */
	dlm_clean_master_list(dlm, dead_node);

	/*
	 * now clean up all lock resources.  there are two rules:
	 *
	 * 1) अगर the dead node was the master, move the lockres
	 *    to the recovering list.  set the RECOVERING flag.
	 *    this lockres needs to be cleaned up beक्रमe it can
	 *    be used further.
	 *
	 * 2) अगर this node was the master, हटाओ all locks from
	 *    each of the lockres queues that were owned by the
	 *    dead node.  once recovery finishes, the dlm thपढ़ो
	 *    can be kicked again to see अगर any ASTs or BASTs
	 *    need to be fired as a result.
	 */
	क्रम (i = 0; i < DLM_HASH_BUCKETS; i++) अणु
		bucket = dlm_lockres_hash(dlm, i);
		hlist_क्रम_each_entry_safe(res, पंचांगp, bucket, hash_node) अणु
 			/* always prune any $RECOVERY entries क्रम dead nodes,
 			 * otherwise hangs can occur during later recovery */
			अगर (dlm_is_recovery_lock(res->lockname.name,
						 res->lockname.len)) अणु
				spin_lock(&res->spinlock);
				list_क्रम_each_entry(lock, &res->granted, list) अणु
					अगर (lock->ml.node == dead_node) अणु
						mlog(0, "AHA! there was "
						     "a $RECOVERY lock for dead "
						     "node %u (%s)!\n",
						     dead_node, dlm->name);
						list_del_init(&lock->list);
						dlm_lock_put(lock);
						/* Can't schedule
						 * DLM_UNLOCK_FREE_LOCK
						 * - करो manually */
						dlm_lock_put(lock);
						अवरोध;
					पूर्ण
				पूर्ण

				अगर ((res->owner == dead_node) &&
							(res->state & DLM_LOCK_RES_DROPPING_REF)) अणु
					dlm_lockres_get(res);
					__dlm_करो_purge_lockres(dlm, res);
					spin_unlock(&res->spinlock);
					wake_up(&res->wq);
					dlm_lockres_put(res);
					जारी;
				पूर्ण अन्यथा अगर (res->owner == dlm->node_num)
					dlm_lockres_clear_refmap_bit(dlm, res, dead_node);
				spin_unlock(&res->spinlock);
				जारी;
			पूर्ण
			spin_lock(&res->spinlock);
			/* zero the lvb अगर necessary */
			dlm_revalidate_lvb(dlm, res, dead_node);
			अगर (res->owner == dead_node) अणु
				अगर (res->state & DLM_LOCK_RES_DROPPING_REF) अणु
					mlog(0, "%s:%.*s: owned by "
						"dead node %u, this node was "
						"dropping its ref when master died. "
						"continue, purging the lockres.\n",
						dlm->name, res->lockname.len,
						res->lockname.name, dead_node);
					dlm_lockres_get(res);
					__dlm_करो_purge_lockres(dlm, res);
					spin_unlock(&res->spinlock);
					wake_up(&res->wq);
					dlm_lockres_put(res);
					जारी;
				पूर्ण
				dlm_move_lockres_to_recovery_list(dlm, res);
			पूर्ण अन्यथा अगर (res->owner == dlm->node_num) अणु
				dlm_मुक्त_dead_locks(dlm, res, dead_node);
				__dlm_lockres_calc_usage(dlm, res);
			पूर्ण अन्यथा अगर (res->owner == DLM_LOCK_RES_OWNER_UNKNOWN) अणु
				अगर (test_bit(dead_node, res->refmap)) अणु
					mlog(0, "%s:%.*s: dead node %u had a ref, but had "
						"no locks and had not purged before dying\n",
						dlm->name, res->lockname.len,
						res->lockname.name, dead_node);
					dlm_lockres_clear_refmap_bit(dlm, res, dead_node);
				पूर्ण
			पूर्ण
			spin_unlock(&res->spinlock);
		पूर्ण
	पूर्ण

पूर्ण

अटल व्योम __dlm_hb_node_करोwn(काष्ठा dlm_ctxt *dlm, पूर्णांक idx)
अणु
	निश्चित_spin_locked(&dlm->spinlock);

	अगर (dlm->reco.new_master == idx) अणु
		mlog(0, "%s: recovery master %d just died\n",
		     dlm->name, idx);
		अगर (dlm->reco.state & DLM_RECO_STATE_FINALIZE) अणु
			/* finalize1 was reached, so it is safe to clear
			 * the new_master and dead_node.  that recovery
			 * is complete. */
			mlog(0, "%s: dead master %d had reached "
			     "finalize1 state, clearing\n", dlm->name, idx);
			dlm->reco.state &= ~DLM_RECO_STATE_FINALIZE;
			__dlm_reset_recovery(dlm);
		पूर्ण
	पूर्ण

	/* Clean up join state on node death. */
	अगर (dlm->joining_node == idx) अणु
		mlog(0, "Clearing join state for node %u\n", idx);
		__dlm_set_joining_node(dlm, DLM_LOCK_RES_OWNER_UNKNOWN);
	पूर्ण

	/* check to see अगर the node is alपढ़ोy considered dead */
	अगर (!test_bit(idx, dlm->live_nodes_map)) अणु
		mlog(0, "for domain %s, node %d is already dead. "
		     "another node likely did recovery already.\n",
		     dlm->name, idx);
		वापस;
	पूर्ण

	/* check to see अगर we करो not care about this node */
	अगर (!test_bit(idx, dlm->करोमुख्य_map)) अणु
		/* This also catches the हाल that we get a node करोwn
		 * but haven't joined the करोमुख्य yet. */
		mlog(0, "node %u already removed from domain!\n", idx);
		वापस;
	पूर्ण

	clear_bit(idx, dlm->live_nodes_map);

	/* make sure local cleanup occurs beक्रमe the heartbeat events */
	अगर (!test_bit(idx, dlm->recovery_map))
		dlm_करो_local_recovery_cleanup(dlm, idx);

	/* notअगरy anything attached to the heartbeat events */
	dlm_hb_event_notअगरy_attached(dlm, idx, 0);

	mlog(0, "node %u being removed from domain map!\n", idx);
	clear_bit(idx, dlm->करोमुख्य_map);
	clear_bit(idx, dlm->निकास_करोमुख्य_map);
	/* wake up migration रुकोers अगर a node goes करोwn.
	 * perhaps later we can genericize this क्रम other रुकोers. */
	wake_up(&dlm->migration_wq);

	set_bit(idx, dlm->recovery_map);
पूर्ण

व्योम dlm_hb_node_करोwn_cb(काष्ठा o2nm_node *node, पूर्णांक idx, व्योम *data)
अणु
	काष्ठा dlm_ctxt *dlm = data;

	अगर (!dlm_grab(dlm))
		वापस;

	/*
	 * This will notअगरy any dlm users that a node in our करोमुख्य
	 * went away without notअगरying us first.
	 */
	अगर (test_bit(idx, dlm->करोमुख्य_map))
		dlm_fire_करोमुख्य_eviction_callbacks(dlm, idx);

	spin_lock(&dlm->spinlock);
	__dlm_hb_node_करोwn(dlm, idx);
	spin_unlock(&dlm->spinlock);

	dlm_put(dlm);
पूर्ण

व्योम dlm_hb_node_up_cb(काष्ठा o2nm_node *node, पूर्णांक idx, व्योम *data)
अणु
	काष्ठा dlm_ctxt *dlm = data;

	अगर (!dlm_grab(dlm))
		वापस;

	spin_lock(&dlm->spinlock);
	set_bit(idx, dlm->live_nodes_map);
	/* करो NOT notअगरy mle attached to the heartbeat events.
	 * new nodes are not पूर्णांकeresting in mastery until joined. */
	spin_unlock(&dlm->spinlock);

	dlm_put(dlm);
पूर्ण

अटल व्योम dlm_reco_ast(व्योम *astdata)
अणु
	काष्ठा dlm_ctxt *dlm = astdata;
	mlog(0, "ast for recovery lock fired!, this=%u, dlm=%s\n",
	     dlm->node_num, dlm->name);
पूर्ण
अटल व्योम dlm_reco_bast(व्योम *astdata, पूर्णांक blocked_type)
अणु
	काष्ठा dlm_ctxt *dlm = astdata;
	mlog(0, "bast for recovery lock fired!, this=%u, dlm=%s\n",
	     dlm->node_num, dlm->name);
पूर्ण
अटल व्योम dlm_reco_unlock_ast(व्योम *astdata, क्रमागत dlm_status st)
अणु
	mlog(0, "unlockast for recovery lock fired!\n");
पूर्ण

/*
 * dlm_pick_recovery_master will continually attempt to use
 * dlmlock() on the special "$RECOVERY" lockres with the
 * LKM_NOQUEUE flag to get an EX.  every thपढ़ो that enters
 * this function on each node racing to become the recovery
 * master will not stop attempting this until either:
 * a) this node माला_लो the EX (and becomes the recovery master),
 * or b) dlm->reco.new_master माला_लो set to some nodक्रमागत
 * != O2NM_INVALID_NODE_NUM (another node will करो the reco).
 * so each समय a recovery master is needed, the entire cluster
 * will sync at this poपूर्णांक.  अगर the new master dies, that will
 * be detected in dlm_करो_recovery */
अटल पूर्णांक dlm_pick_recovery_master(काष्ठा dlm_ctxt *dlm)
अणु
	क्रमागत dlm_status ret;
	काष्ठा dlm_lockstatus lksb;
	पूर्णांक status = -EINVAL;

	mlog(0, "starting recovery of %s at %lu, dead=%u, this=%u\n",
	     dlm->name, jअगरfies, dlm->reco.dead_node, dlm->node_num);
again:
	स_रखो(&lksb, 0, माप(lksb));

	ret = dlmlock(dlm, LKM_EXMODE, &lksb, LKM_NOQUEUE|LKM_RECOVERY,
		      DLM_RECOVERY_LOCK_NAME, DLM_RECOVERY_LOCK_NAME_LEN,
		      dlm_reco_ast, dlm, dlm_reco_bast);

	mlog(0, "%s: dlmlock($RECOVERY) returned %d, lksb=%d\n",
	     dlm->name, ret, lksb.status);

	अगर (ret == DLM_NORMAL) अणु
		mlog(0, "dlm=%s dlmlock says I got it (this=%u)\n",
		     dlm->name, dlm->node_num);

		/* got the EX lock.  check to see अगर another node
		 * just became the reco master */
		अगर (dlm_reco_master_पढ़ोy(dlm)) अणु
			mlog(0, "%s: got reco EX lock, but %u will "
			     "do the recovery\n", dlm->name,
			     dlm->reco.new_master);
			status = -EEXIST;
		पूर्ण अन्यथा अणु
			status = 0;

			/* see अगर recovery was alपढ़ोy finished अन्यथाwhere */
			spin_lock(&dlm->spinlock);
			अगर (dlm->reco.dead_node == O2NM_INVALID_NODE_NUM) अणु
				status = -EINVAL;
				mlog(0, "%s: got reco EX lock, but "
				     "node got recovered already\n", dlm->name);
				अगर (dlm->reco.new_master != O2NM_INVALID_NODE_NUM) अणु
					mlog(ML_ERROR, "%s: new master is %u "
					     "but no dead node!\n",
					     dlm->name, dlm->reco.new_master);
					BUG();
				पूर्ण
			पूर्ण
			spin_unlock(&dlm->spinlock);
		पूर्ण

		/* अगर this node has actually become the recovery master,
		 * set the master and send the messages to begin recovery */
		अगर (!status) अणु
			mlog(0, "%s: dead=%u, this=%u, sending "
			     "begin_reco now\n", dlm->name,
			     dlm->reco.dead_node, dlm->node_num);
			status = dlm_send_begin_reco_message(dlm,
				      dlm->reco.dead_node);
			/* this always succeeds */
			BUG_ON(status);

			/* set the new_master to this node */
			spin_lock(&dlm->spinlock);
			dlm_set_reco_master(dlm, dlm->node_num);
			spin_unlock(&dlm->spinlock);
		पूर्ण

		/* recovery lock is a special हाल.  ast will not get fired,
		 * so just go ahead and unlock it. */
		ret = dlmunlock(dlm, &lksb, 0, dlm_reco_unlock_ast, dlm);
		अगर (ret == DLM_DENIED) अणु
			mlog(0, "got DLM_DENIED, trying LKM_CANCEL\n");
			ret = dlmunlock(dlm, &lksb, LKM_CANCEL, dlm_reco_unlock_ast, dlm);
		पूर्ण
		अगर (ret != DLM_NORMAL) अणु
			/* this would really suck. this could only happen
			 * अगर there was a network error during the unlock
			 * because of node death.  this means the unlock
			 * is actually "done" and the lock काष्ठाure is
			 * even मुक्तd.  we can जारी, but only
			 * because this specअगरic lock name is special. */
			mlog(ML_ERROR, "dlmunlock returned %d\n", ret);
		पूर्ण
	पूर्ण अन्यथा अगर (ret == DLM_NOTQUEUED) अणु
		mlog(0, "dlm=%s dlmlock says another node got it (this=%u)\n",
		     dlm->name, dlm->node_num);
		/* another node is master. रुको on
		 * reco.new_master != O2NM_INVALID_NODE_NUM
		 * क्रम at most one second */
		रुको_event_समयout(dlm->dlm_reco_thपढ़ो_wq,
					 dlm_reco_master_पढ़ोy(dlm),
					 msecs_to_jअगरfies(1000));
		अगर (!dlm_reco_master_पढ़ोy(dlm)) अणु
			mlog(0, "%s: reco master taking awhile\n",
			     dlm->name);
			जाओ again;
		पूर्ण
		/* another node has inक्रमmed this one that it is reco master */
		mlog(0, "%s: reco master %u is ready to recover %u\n",
		     dlm->name, dlm->reco.new_master, dlm->reco.dead_node);
		status = -EEXIST;
	पूर्ण अन्यथा अगर (ret == DLM_RECOVERING) अणु
		mlog(0, "dlm=%s dlmlock says master node died (this=%u)\n",
		     dlm->name, dlm->node_num);
		जाओ again;
	पूर्ण अन्यथा अणु
		काष्ठा dlm_lock_resource *res;

		/* dlmlock वापसed something other than NOTQUEUED or NORMAL */
		mlog(ML_ERROR, "%s: got %s from dlmlock($RECOVERY), "
		     "lksb.status=%s\n", dlm->name, dlm_errname(ret),
		     dlm_errname(lksb.status));
		res = dlm_lookup_lockres(dlm, DLM_RECOVERY_LOCK_NAME,
					 DLM_RECOVERY_LOCK_NAME_LEN);
		अगर (res) अणु
			dlm_prपूर्णांक_one_lock_resource(res);
			dlm_lockres_put(res);
		पूर्ण अन्यथा अणु
			mlog(ML_ERROR, "recovery lock not found\n");
		पूर्ण
		BUG();
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक dlm_send_begin_reco_message(काष्ठा dlm_ctxt *dlm, u8 dead_node)
अणु
	काष्ठा dlm_begin_reco br;
	पूर्णांक ret = 0;
	काष्ठा dlm_node_iter iter;
	पूर्णांक nodक्रमागत;
	पूर्णांक status;

	mlog(0, "%s: dead node is %u\n", dlm->name, dead_node);

	spin_lock(&dlm->spinlock);
	dlm_node_iter_init(dlm->करोमुख्य_map, &iter);
	spin_unlock(&dlm->spinlock);

	clear_bit(dead_node, iter.node_map);

	स_रखो(&br, 0, माप(br));
	br.node_idx = dlm->node_num;
	br.dead_node = dead_node;

	जबतक ((nodक्रमागत = dlm_node_iter_next(&iter)) >= 0) अणु
		ret = 0;
		अगर (nodक्रमागत == dead_node) अणु
			mlog(0, "not sending begin reco to dead node "
				  "%u\n", dead_node);
			जारी;
		पूर्ण
		अगर (nodक्रमागत == dlm->node_num) अणु
			mlog(0, "not sending begin reco to self\n");
			जारी;
		पूर्ण
retry:
		ret = -EINVAL;
		mlog(0, "attempting to send begin reco msg to %d\n",
			  nodक्रमागत);
		ret = o2net_send_message(DLM_BEGIN_RECO_MSG, dlm->key,
					 &br, माप(br), nodक्रमागत, &status);
		/* negative status is handled ok by caller here */
		अगर (ret >= 0)
			ret = status;
		अगर (dlm_is_host_करोwn(ret)) अणु
			/* node is करोwn.  not involved in recovery
			 * so just keep going */
			mlog(ML_NOTICE, "%s: node %u was down when sending "
			     "begin reco msg (%d)\n", dlm->name, nodक्रमागत, ret);
			ret = 0;
		पूर्ण

		/*
		 * Prior to commit aad1b15310b9bcd59fa81ab8f2b1513b59553ea8,
		 * dlm_begin_reco_handler() वापसed EAGAIN and not -EAGAIN.
		 * We are handling both क्रम compatibility reasons.
		 */
		अगर (ret == -EAGAIN || ret == EAGAIN) अणु
			mlog(0, "%s: trying to start recovery of node "
			     "%u, but node %u is waiting for last recovery "
			     "to complete, backoff for a bit\n", dlm->name,
			     dead_node, nodक्रमागत);
			msleep(100);
			जाओ retry;
		पूर्ण
		अगर (ret < 0) अणु
			काष्ठा dlm_lock_resource *res;

			/* this is now a serious problem, possibly ENOMEM
			 * in the network stack.  must retry */
			mlog_त्रुटि_सं(ret);
			mlog(ML_ERROR, "begin reco of dlm %s to node %u "
			     "returned %d\n", dlm->name, nodक्रमागत, ret);
			res = dlm_lookup_lockres(dlm, DLM_RECOVERY_LOCK_NAME,
						 DLM_RECOVERY_LOCK_NAME_LEN);
			अगर (res) अणु
				dlm_prपूर्णांक_one_lock_resource(res);
				dlm_lockres_put(res);
			पूर्ण अन्यथा अणु
				mlog(ML_ERROR, "recovery lock not found\n");
			पूर्ण
			/* sleep क्रम a bit in hopes that we can aव्योम
			 * another ENOMEM */
			msleep(100);
			जाओ retry;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक dlm_begin_reco_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			   व्योम **ret_data)
अणु
	काष्ठा dlm_ctxt *dlm = data;
	काष्ठा dlm_begin_reco *br = (काष्ठा dlm_begin_reco *)msg->buf;

	/* ok to वापस 0, करोमुख्य has gone away */
	अगर (!dlm_grab(dlm))
		वापस 0;

	spin_lock(&dlm->spinlock);
	अगर (dlm->reco.state & DLM_RECO_STATE_FINALIZE) अणु
		mlog(0, "%s: node %u wants to recover node %u (%u:%u) "
		     "but this node is in finalize state, waiting on finalize2\n",
		     dlm->name, br->node_idx, br->dead_node,
		     dlm->reco.dead_node, dlm->reco.new_master);
		spin_unlock(&dlm->spinlock);
		dlm_put(dlm);
		वापस -EAGAIN;
	पूर्ण
	spin_unlock(&dlm->spinlock);

	mlog(0, "%s: node %u wants to recover node %u (%u:%u)\n",
	     dlm->name, br->node_idx, br->dead_node,
	     dlm->reco.dead_node, dlm->reco.new_master);

	dlm_fire_करोमुख्य_eviction_callbacks(dlm, br->dead_node);

	spin_lock(&dlm->spinlock);
	अगर (dlm->reco.new_master != O2NM_INVALID_NODE_NUM) अणु
		अगर (test_bit(dlm->reco.new_master, dlm->recovery_map)) अणु
			mlog(0, "%s: new_master %u died, changing "
			     "to %u\n", dlm->name, dlm->reco.new_master,
			     br->node_idx);
		पूर्ण अन्यथा अणु
			mlog(0, "%s: new_master %u NOT DEAD, changing "
			     "to %u\n", dlm->name, dlm->reco.new_master,
			     br->node_idx);
			/* may not have seen the new master as dead yet */
		पूर्ण
	पूर्ण
	अगर (dlm->reco.dead_node != O2NM_INVALID_NODE_NUM) अणु
		mlog(ML_NOTICE, "%s: dead_node previously set to %u, "
		     "node %u changing it to %u\n", dlm->name,
		     dlm->reco.dead_node, br->node_idx, br->dead_node);
	पूर्ण
	dlm_set_reco_master(dlm, br->node_idx);
	dlm_set_reco_dead_node(dlm, br->dead_node);
	अगर (!test_bit(br->dead_node, dlm->recovery_map)) अणु
		mlog(0, "recovery master %u sees %u as dead, but this "
		     "node has not yet.  marking %u as dead\n",
		     br->node_idx, br->dead_node, br->dead_node);
		अगर (!test_bit(br->dead_node, dlm->करोमुख्य_map) ||
		    !test_bit(br->dead_node, dlm->live_nodes_map))
			mlog(0, "%u not in domain/live_nodes map "
			     "so setting it in reco map manually\n",
			     br->dead_node);
		/* क्रमce the recovery cleanup in __dlm_hb_node_करोwn
		 * both of these will be cleared in a moment */
		set_bit(br->dead_node, dlm->करोमुख्य_map);
		set_bit(br->dead_node, dlm->live_nodes_map);
		__dlm_hb_node_करोwn(dlm, br->dead_node);
	पूर्ण
	spin_unlock(&dlm->spinlock);

	dlm_kick_recovery_thपढ़ो(dlm);

	mlog(0, "%s: recovery started by node %u, for %u (%u:%u)\n",
	     dlm->name, br->node_idx, br->dead_node,
	     dlm->reco.dead_node, dlm->reco.new_master);

	dlm_put(dlm);
	वापस 0;
पूर्ण

#घोषणा DLM_FINALIZE_STAGE2  0x01
अटल पूर्णांक dlm_send_finalize_reco_message(काष्ठा dlm_ctxt *dlm)
अणु
	पूर्णांक ret = 0;
	काष्ठा dlm_finalize_reco fr;
	काष्ठा dlm_node_iter iter;
	पूर्णांक nodक्रमागत;
	पूर्णांक status;
	पूर्णांक stage = 1;

	mlog(0, "finishing recovery for node %s:%u, "
	     "stage %d\n", dlm->name, dlm->reco.dead_node, stage);

	spin_lock(&dlm->spinlock);
	dlm_node_iter_init(dlm->करोमुख्य_map, &iter);
	spin_unlock(&dlm->spinlock);

stage2:
	स_रखो(&fr, 0, माप(fr));
	fr.node_idx = dlm->node_num;
	fr.dead_node = dlm->reco.dead_node;
	अगर (stage == 2)
		fr.flags |= DLM_FINALIZE_STAGE2;

	जबतक ((nodक्रमागत = dlm_node_iter_next(&iter)) >= 0) अणु
		अगर (nodक्रमागत == dlm->node_num)
			जारी;
		ret = o2net_send_message(DLM_FINALIZE_RECO_MSG, dlm->key,
					 &fr, माप(fr), nodक्रमागत, &status);
		अगर (ret >= 0)
			ret = status;
		अगर (ret < 0) अणु
			mlog(ML_ERROR, "Error %d when sending message %u (key "
			     "0x%x) to node %u\n", ret, DLM_FINALIZE_RECO_MSG,
			     dlm->key, nodक्रमागत);
			अगर (dlm_is_host_करोwn(ret)) अणु
				/* this has no effect on this recovery
				 * session, so set the status to zero to
				 * finish out the last recovery */
				mlog(ML_ERROR, "node %u went down after this "
				     "node finished recovery.\n", nodक्रमागत);
				ret = 0;
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (stage == 1) अणु
		/* reset the node_iter back to the top and send finalize2 */
		iter.curnode = -1;
		stage = 2;
		जाओ stage2;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक dlm_finalize_reco_handler(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
			      व्योम **ret_data)
अणु
	काष्ठा dlm_ctxt *dlm = data;
	काष्ठा dlm_finalize_reco *fr = (काष्ठा dlm_finalize_reco *)msg->buf;
	पूर्णांक stage = 1;

	/* ok to वापस 0, करोमुख्य has gone away */
	अगर (!dlm_grab(dlm))
		वापस 0;

	अगर (fr->flags & DLM_FINALIZE_STAGE2)
		stage = 2;

	mlog(0, "%s: node %u finalizing recovery stage%d of "
	     "node %u (%u:%u)\n", dlm->name, fr->node_idx, stage,
	     fr->dead_node, dlm->reco.dead_node, dlm->reco.new_master);

	spin_lock(&dlm->spinlock);

	अगर (dlm->reco.new_master != fr->node_idx) अणु
		mlog(ML_ERROR, "node %u sent recovery finalize msg, but node "
		     "%u is supposed to be the new master, dead=%u\n",
		     fr->node_idx, dlm->reco.new_master, fr->dead_node);
		BUG();
	पूर्ण
	अगर (dlm->reco.dead_node != fr->dead_node) अणु
		mlog(ML_ERROR, "node %u sent recovery finalize msg for dead "
		     "node %u, but node %u is supposed to be dead\n",
		     fr->node_idx, fr->dead_node, dlm->reco.dead_node);
		BUG();
	पूर्ण

	चयन (stage) अणु
		हाल 1:
			dlm_finish_local_lockres_recovery(dlm, fr->dead_node, fr->node_idx);
			अगर (dlm->reco.state & DLM_RECO_STATE_FINALIZE) अणु
				mlog(ML_ERROR, "%s: received finalize1 from "
				     "new master %u for dead node %u, but "
				     "this node has already received it!\n",
				     dlm->name, fr->node_idx, fr->dead_node);
				dlm_prपूर्णांक_reco_node_status(dlm);
				BUG();
			पूर्ण
			dlm->reco.state |= DLM_RECO_STATE_FINALIZE;
			spin_unlock(&dlm->spinlock);
			अवरोध;
		हाल 2:
			अगर (!(dlm->reco.state & DLM_RECO_STATE_FINALIZE)) अणु
				mlog(ML_ERROR, "%s: received finalize2 from "
				     "new master %u for dead node %u, but "
				     "this node did not have finalize1!\n",
				     dlm->name, fr->node_idx, fr->dead_node);
				dlm_prपूर्णांक_reco_node_status(dlm);
				BUG();
			पूर्ण
			dlm->reco.state &= ~DLM_RECO_STATE_FINALIZE;
			__dlm_reset_recovery(dlm);
			spin_unlock(&dlm->spinlock);
			dlm_kick_recovery_thपढ़ो(dlm);
			अवरोध;
	पूर्ण

	mlog(0, "%s: recovery done, reco master was %u, dead now %u, master now %u\n",
	     dlm->name, fr->node_idx, dlm->reco.dead_node, dlm->reco.new_master);

	dlm_put(dlm);
	वापस 0;
पूर्ण
