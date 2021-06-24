<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * Copyright (C) 2005 Oracle.  All rights reserved.
 */

/* This quorum hack is only here until we transition to some more rational
 * approach that is driven from userspace.  Honest.  No foolin'.
 *
 * Imagine two nodes lose network connectivity to each other but they're still
 * up and operating in every other way.  Presumably a network समयout indicates
 * that a node is broken and should be recovered.  They can't both recover each
 * other and both carry on without serialising their access to the file प्रणाली.
 * They need to decide who is authoritative.  Now extend that problem to
 * arbitrary groups of nodes losing connectivity between each other.
 *
 * So we declare that a node which has given up on connecting to a majority
 * of nodes who are still heartbeating will fence itself.
 *
 * There are huge opportunities क्रम races here.  After we give up on a node's
 * connection we need to रुको दीर्घ enough to give heartbeat an opportunity
 * to declare the node as truly dead.  We also need to be careful with the
 * race between when we see a node start heartbeating and when we connect
 * to it.
 *
 * So nodes that are in this transtion put a hold on the quorum decision
 * with a counter.  As they fall out of this transition they drop the count
 * and अगर they're the last, they fire off the decision.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/reboot.h>

#समावेश "heartbeat.h"
#समावेश "nodemanager.h"
#घोषणा MLOG_MASK_PREFIX ML_QUORUM
#समावेश "masklog.h"
#समावेश "quorum.h"

अटल काष्ठा o2quo_state अणु
	spinlock_t		qs_lock;
	काष्ठा work_काष्ठा	qs_work;
	पूर्णांक			qs_pending;
	पूर्णांक			qs_heartbeating;
	अचिन्हित दीर्घ		qs_hb_bm[BITS_TO_LONGS(O2NM_MAX_NODES)];
	पूर्णांक			qs_connected;
	अचिन्हित दीर्घ		qs_conn_bm[BITS_TO_LONGS(O2NM_MAX_NODES)];
	पूर्णांक			qs_holds;
	अचिन्हित दीर्घ		qs_hold_bm[BITS_TO_LONGS(O2NM_MAX_NODES)];
पूर्ण o2quo_state;

/* this is horribly heavy-handed.  It should instead flip the file
 * प्रणाली RO and call some userspace script. */
अटल व्योम o2quo_fence_self(व्योम)
अणु
	/* panic spins with पूर्णांकerrupts enabled.  with preempt
	 * thपढ़ोs can still schedule, etc, etc */
	o2hb_stop_all_regions();

	चयन (o2nm_single_cluster->cl_fence_method) अणु
	हाल O2NM_FENCE_PANIC:
		panic("*** ocfs2 is very sorry to be fencing this system by "
		      "panicing ***\n");
		अवरोध;
	शेष:
		WARN_ON(o2nm_single_cluster->cl_fence_method >=
			O2NM_FENCE_METHODS);
		fallthrough;
	हाल O2NM_FENCE_RESET:
		prपूर्णांकk(KERN_ERR "*** ocfs2 is very sorry to be fencing this "
		       "system by restarting ***\n");
		emergency_restart();
		अवरोध;
	पूर्ण
पूर्ण

/* Indicate that a समयout occurred on a heartbeat region ग_लिखो. The
 * other nodes in the cluster may consider us dead at that समय so we
 * want to "fence" ourselves so that we करोn't scribble on the disk
 * after they think they've recovered us. This can't solve all
 * problems related to ग_लिखोout after recovery but this hack can at
 * least बंद some of those gaps. When we have real fencing, this can
 * go away as our node would be fenced बाह्यally beक्रमe other nodes
 * begin recovery. */
व्योम o2quo_disk_समयout(व्योम)
अणु
	o2quo_fence_self();
पूर्ण

अटल व्योम o2quo_make_decision(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक quorum;
	पूर्णांक lowest_hb, lowest_reachable = 0, fence = 0;
	काष्ठा o2quo_state *qs = &o2quo_state;

	spin_lock(&qs->qs_lock);

	lowest_hb = find_first_bit(qs->qs_hb_bm, O2NM_MAX_NODES);
	अगर (lowest_hb != O2NM_MAX_NODES)
		lowest_reachable = test_bit(lowest_hb, qs->qs_conn_bm);

	mlog(0, "heartbeating: %d, connected: %d, "
	     "lowest: %d (%sreachable)\n", qs->qs_heartbeating,
	     qs->qs_connected, lowest_hb, lowest_reachable ? "" : "un");

	अगर (!test_bit(o2nm_this_node(), qs->qs_hb_bm) ||
	    qs->qs_heartbeating == 1)
		जाओ out;

	अगर (qs->qs_heartbeating & 1) अणु
		/* the odd numbered cluster हाल is straight क्रमward --
		 * अगर we can't talk to the majority we're hosed */
		quorum = (qs->qs_heartbeating + 1)/2;
		अगर (qs->qs_connected < quorum) अणु
			mlog(ML_ERROR, "fencing this node because it is "
			     "only connected to %u nodes and %u is needed "
			     "to make a quorum out of %u heartbeating nodes\n",
			     qs->qs_connected, quorum,
			     qs->qs_heartbeating);
			fence = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* the even numbered cluster adds the possibility of each half
		 * of the cluster being able to talk amongst themselves.. in
		 * that हाल we're hosed if we can't talk to the group that has
		 * the lowest numbered node */
		quorum = qs->qs_heartbeating / 2;
		अगर (qs->qs_connected < quorum) अणु
			mlog(ML_ERROR, "fencing this node because it is "
			     "only connected to %u nodes and %u is needed "
			     "to make a quorum out of %u heartbeating nodes\n",
			     qs->qs_connected, quorum,
			     qs->qs_heartbeating);
			fence = 1;
		पूर्ण
		अन्यथा अगर ((qs->qs_connected == quorum) &&
			 !lowest_reachable) अणु
			mlog(ML_ERROR, "fencing this node because it is "
			     "connected to a half-quorum of %u out of %u "
			     "nodes which doesn't include the lowest active "
			     "node %u\n", quorum, qs->qs_heartbeating,
			     lowest_hb);
			fence = 1;
		पूर्ण
	पूर्ण

out:
	अगर (fence) अणु
		spin_unlock(&qs->qs_lock);
		o2quo_fence_self();
	पूर्ण अन्यथा अणु
		mlog(ML_NOTICE, "not fencing this node, heartbeating: %d, "
			"connected: %d, lowest: %d (%sreachable)\n",
			qs->qs_heartbeating, qs->qs_connected, lowest_hb,
			lowest_reachable ? "" : "un");
		spin_unlock(&qs->qs_lock);

	पूर्ण

पूर्ण

अटल व्योम o2quo_set_hold(काष्ठा o2quo_state *qs, u8 node)
अणु
	निश्चित_spin_locked(&qs->qs_lock);

	अगर (!test_and_set_bit(node, qs->qs_hold_bm)) अणु
		qs->qs_holds++;
		mlog_bug_on_msg(qs->qs_holds == O2NM_MAX_NODES,
			        "node %u\n", node);
		mlog(0, "node %u, %d total\n", node, qs->qs_holds);
	पूर्ण
पूर्ण

अटल व्योम o2quo_clear_hold(काष्ठा o2quo_state *qs, u8 node)
अणु
	निश्चित_spin_locked(&qs->qs_lock);

	अगर (test_and_clear_bit(node, qs->qs_hold_bm)) अणु
		mlog(0, "node %u, %d total\n", node, qs->qs_holds - 1);
		अगर (--qs->qs_holds == 0) अणु
			अगर (qs->qs_pending) अणु
				qs->qs_pending = 0;
				schedule_work(&qs->qs_work);
			पूर्ण
		पूर्ण
		mlog_bug_on_msg(qs->qs_holds < 0, "node %u, holds %d\n",
				node, qs->qs_holds);
	पूर्ण
पूर्ण

/* as a node comes up we delay the quorum decision until we know the fate of
 * the connection.  the hold will be droped in conn_up or hb_करोwn.  it might be
 * perpetuated by con_err until hb_करोwn.  अगर we alपढ़ोy have a conn, we might
 * be dropping a hold that conn_up got. */
व्योम o2quo_hb_up(u8 node)
अणु
	काष्ठा o2quo_state *qs = &o2quo_state;

	spin_lock(&qs->qs_lock);

	qs->qs_heartbeating++;
	mlog_bug_on_msg(qs->qs_heartbeating == O2NM_MAX_NODES,
		        "node %u\n", node);
	mlog_bug_on_msg(test_bit(node, qs->qs_hb_bm), "node %u\n", node);
	set_bit(node, qs->qs_hb_bm);

	mlog(0, "node %u, %d total\n", node, qs->qs_heartbeating);

	अगर (!test_bit(node, qs->qs_conn_bm))
		o2quo_set_hold(qs, node);
	अन्यथा
		o2quo_clear_hold(qs, node);

	spin_unlock(&qs->qs_lock);
पूर्ण

/* hb going करोwn releases any holds we might have had due to this node from
 * conn_up, conn_err, or hb_up */
व्योम o2quo_hb_करोwn(u8 node)
अणु
	काष्ठा o2quo_state *qs = &o2quo_state;

	spin_lock(&qs->qs_lock);

	qs->qs_heartbeating--;
	mlog_bug_on_msg(qs->qs_heartbeating < 0,
			"node %u, %d heartbeating\n",
			node, qs->qs_heartbeating);
	mlog_bug_on_msg(!test_bit(node, qs->qs_hb_bm), "node %u\n", node);
	clear_bit(node, qs->qs_hb_bm);

	mlog(0, "node %u, %d total\n", node, qs->qs_heartbeating);

	o2quo_clear_hold(qs, node);

	spin_unlock(&qs->qs_lock);
पूर्ण

/* this tells us that we've decided that the node is still heartbeating
 * even though we've lost it's conn.  it must only be called after conn_err
 * and indicates that we must now make a quorum decision in the future,
 * though we might be करोing so after रुकोing क्रम holds to drain.  Here
 * we'll be dropping the hold from conn_err. */
व्योम o2quo_hb_still_up(u8 node)
अणु
	काष्ठा o2quo_state *qs = &o2quo_state;

	spin_lock(&qs->qs_lock);

	mlog(0, "node %u\n", node);

	qs->qs_pending = 1;
	o2quo_clear_hold(qs, node);

	spin_unlock(&qs->qs_lock);
पूर्ण

/* This is analogous to hb_up.  as a node's connection comes up we delay the
 * quorum decision until we see it heartbeating.  the hold will be droped in
 * hb_up or hb_करोwn.  it might be perpetuated by con_err until hb_करोwn.  अगर
 * it's alपढ़ोy heartbeating we might be dropping a hold that conn_up got.
 * */
व्योम o2quo_conn_up(u8 node)
अणु
	काष्ठा o2quo_state *qs = &o2quo_state;

	spin_lock(&qs->qs_lock);

	qs->qs_connected++;
	mlog_bug_on_msg(qs->qs_connected == O2NM_MAX_NODES,
		        "node %u\n", node);
	mlog_bug_on_msg(test_bit(node, qs->qs_conn_bm), "node %u\n", node);
	set_bit(node, qs->qs_conn_bm);

	mlog(0, "node %u, %d total\n", node, qs->qs_connected);

	अगर (!test_bit(node, qs->qs_hb_bm))
		o2quo_set_hold(qs, node);
	अन्यथा
		o2quo_clear_hold(qs, node);

	spin_unlock(&qs->qs_lock);
पूर्ण

/* we've decided that we won't ever be connecting to the node again.  if it's
 * still heartbeating we grab a hold that will delay decisions until either the
 * node stops heartbeating from hb_करोwn or the caller decides that the node is
 * still up and calls still_up */
व्योम o2quo_conn_err(u8 node)
अणु
	काष्ठा o2quo_state *qs = &o2quo_state;

	spin_lock(&qs->qs_lock);

	अगर (test_bit(node, qs->qs_conn_bm)) अणु
		qs->qs_connected--;
		mlog_bug_on_msg(qs->qs_connected < 0,
				"node %u, connected %d\n",
				node, qs->qs_connected);

		clear_bit(node, qs->qs_conn_bm);

		अगर (test_bit(node, qs->qs_hb_bm))
			o2quo_set_hold(qs, node);
	पूर्ण

	mlog(0, "node %u, %d total\n", node, qs->qs_connected);


	spin_unlock(&qs->qs_lock);
पूर्ण

व्योम o2quo_init(व्योम)
अणु
	काष्ठा o2quo_state *qs = &o2quo_state;

	spin_lock_init(&qs->qs_lock);
	INIT_WORK(&qs->qs_work, o2quo_make_decision);
पूर्ण

व्योम o2quo_निकास(व्योम)
अणु
	काष्ठा o2quo_state *qs = &o2quo_state;

	flush_work(&qs->qs_work);
पूर्ण
