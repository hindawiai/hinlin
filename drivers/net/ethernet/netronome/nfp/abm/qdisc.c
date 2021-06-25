<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2018 Netronome Systems, Inc. */

#समावेश <linux/rtnetlink.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/red.h>

#समावेश "../nfpcore/nfp_cpp.h"
#समावेश "../nfp_app.h"
#समावेश "../nfp_main.h"
#समावेश "../nfp_net.h"
#समावेश "../nfp_port.h"
#समावेश "main.h"

अटल bool nfp_abm_qdisc_is_red(काष्ठा nfp_qdisc *qdisc)
अणु
	वापस qdisc->type == NFP_QDISC_RED || qdisc->type == NFP_QDISC_GRED;
पूर्ण

अटल bool nfp_abm_qdisc_child_valid(काष्ठा nfp_qdisc *qdisc, अचिन्हित पूर्णांक id)
अणु
	वापस qdisc->children[id] &&
	       qdisc->children[id] != NFP_QDISC_UNTRACKED;
पूर्ण

अटल व्योम *nfp_abm_qdisc_tree_deref_slot(व्योम __rcu **slot)
अणु
	वापस rtnl_dereference(*slot);
पूर्ण

अटल व्योम
nfp_abm_stats_propagate(काष्ठा nfp_alink_stats *parent,
			काष्ठा nfp_alink_stats *child)
अणु
	parent->tx_pkts		+= child->tx_pkts;
	parent->tx_bytes	+= child->tx_bytes;
	parent->backlog_pkts	+= child->backlog_pkts;
	parent->backlog_bytes	+= child->backlog_bytes;
	parent->overlimits	+= child->overlimits;
	parent->drops		+= child->drops;
पूर्ण

अटल व्योम
nfp_abm_stats_update_red(काष्ठा nfp_abm_link *alink, काष्ठा nfp_qdisc *qdisc,
			 अचिन्हित पूर्णांक queue)
अणु
	काष्ठा nfp_cpp *cpp = alink->abm->app->cpp;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	अगर (!qdisc->offloaded)
		वापस;

	क्रम (i = 0; i < qdisc->red.num_bands; i++) अणु
		err = nfp_abm_ctrl_पढ़ो_q_stats(alink, i, queue,
						&qdisc->red.band[i].stats);
		अगर (err)
			nfp_err(cpp, "RED stats (%d, %d) read failed with error %d\n",
				i, queue, err);

		err = nfp_abm_ctrl_पढ़ो_q_xstats(alink, i, queue,
						 &qdisc->red.band[i].xstats);
		अगर (err)
			nfp_err(cpp, "RED xstats (%d, %d) read failed with error %d\n",
				i, queue, err);
	पूर्ण
पूर्ण

अटल व्योम
nfp_abm_stats_update_mq(काष्ठा nfp_abm_link *alink, काष्ठा nfp_qdisc *qdisc)
अणु
	अचिन्हित पूर्णांक i;

	अगर (qdisc->type != NFP_QDISC_MQ)
		वापस;

	क्रम (i = 0; i < alink->total_queues; i++)
		अगर (nfp_abm_qdisc_child_valid(qdisc, i))
			nfp_abm_stats_update_red(alink, qdisc->children[i], i);
पूर्ण

अटल व्योम __nfp_abm_stats_update(काष्ठा nfp_abm_link *alink, u64 समय_now)
अणु
	alink->last_stats_update = समय_now;
	अगर (alink->root_qdisc)
		nfp_abm_stats_update_mq(alink, alink->root_qdisc);
पूर्ण

अटल व्योम nfp_abm_stats_update(काष्ठा nfp_abm_link *alink)
अणु
	u64 now;

	/* Limit the frequency of updates - stats of non-leaf qdiscs are a sum
	 * of all their leafs, so we would पढ़ो the same stat multiple बार
	 * क्रम every dump.
	 */
	now = kसमय_get();
	अगर (now - alink->last_stats_update < NFP_ABM_STATS_REFRESH_IVAL)
		वापस;

	__nfp_abm_stats_update(alink, now);
पूर्ण

अटल व्योम
nfp_abm_qdisc_unlink_children(काष्ठा nfp_qdisc *qdisc,
			      अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक end)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = start; i < end; i++)
		अगर (nfp_abm_qdisc_child_valid(qdisc, i)) अणु
			qdisc->children[i]->use_cnt--;
			qdisc->children[i] = शून्य;
		पूर्ण
पूर्ण

अटल व्योम
nfp_abm_qdisc_offload_stop(काष्ठा nfp_abm_link *alink, काष्ठा nfp_qdisc *qdisc)
अणु
	अचिन्हित पूर्णांक i;

	/* Don't complain when qdisc is getting unlinked */
	अगर (qdisc->use_cnt)
		nfp_warn(alink->abm->app->cpp, "Offload of '%08x' stopped\n",
			 qdisc->handle);

	अगर (!nfp_abm_qdisc_is_red(qdisc))
		वापस;

	क्रम (i = 0; i < qdisc->red.num_bands; i++) अणु
		qdisc->red.band[i].stats.backlog_pkts = 0;
		qdisc->red.band[i].stats.backlog_bytes = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक
__nfp_abm_stats_init(काष्ठा nfp_abm_link *alink, अचिन्हित पूर्णांक band,
		     अचिन्हित पूर्णांक queue, काष्ठा nfp_alink_stats *prev_stats,
		     काष्ठा nfp_alink_xstats *prev_xstats)
अणु
	u64 backlog_pkts, backlog_bytes;
	पूर्णांक err;

	/* Don't touch the backlog, backlog can only be reset after it has
	 * been reported back to the tc qdisc stats.
	 */
	backlog_pkts = prev_stats->backlog_pkts;
	backlog_bytes = prev_stats->backlog_bytes;

	err = nfp_abm_ctrl_पढ़ो_q_stats(alink, band, queue, prev_stats);
	अगर (err) अणु
		nfp_err(alink->abm->app->cpp,
			"RED stats init (%d, %d) failed with error %d\n",
			band, queue, err);
		वापस err;
	पूर्ण

	err = nfp_abm_ctrl_पढ़ो_q_xstats(alink, band, queue, prev_xstats);
	अगर (err) अणु
		nfp_err(alink->abm->app->cpp,
			"RED xstats init (%d, %d) failed with error %d\n",
			band, queue, err);
		वापस err;
	पूर्ण

	prev_stats->backlog_pkts = backlog_pkts;
	prev_stats->backlog_bytes = backlog_bytes;
	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_abm_stats_init(काष्ठा nfp_abm_link *alink, काष्ठा nfp_qdisc *qdisc,
		   अचिन्हित पूर्णांक queue)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < qdisc->red.num_bands; i++) अणु
		err = __nfp_abm_stats_init(alink, i, queue,
					   &qdisc->red.band[i].prev_stats,
					   &qdisc->red.band[i].prev_xstats);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
nfp_abm_offload_compile_red(काष्ठा nfp_abm_link *alink, काष्ठा nfp_qdisc *qdisc,
			    अचिन्हित पूर्णांक queue)
अणु
	bool good_red, good_gred;
	अचिन्हित पूर्णांक i;

	good_red = qdisc->type == NFP_QDISC_RED &&
		   qdisc->params_ok &&
		   qdisc->use_cnt == 1 &&
		   !alink->has_prio &&
		   !qdisc->children[0];
	good_gred = qdisc->type == NFP_QDISC_GRED &&
		    qdisc->params_ok &&
		    qdisc->use_cnt == 1;
	qdisc->offload_mark = good_red || good_gred;

	/* If we are starting offload init prev_stats */
	अगर (qdisc->offload_mark && !qdisc->offloaded)
		अगर (nfp_abm_stats_init(alink, qdisc, queue))
			qdisc->offload_mark = false;

	अगर (!qdisc->offload_mark)
		वापस;

	क्रम (i = 0; i < alink->abm->num_bands; i++) अणु
		क्रमागत nfp_abm_q_action act;

		nfp_abm_ctrl_set_q_lvl(alink, i, queue,
				       qdisc->red.band[i].threshold);
		act = qdisc->red.band[i].ecn ?
			NFP_ABM_ACT_MARK_DROP : NFP_ABM_ACT_DROP;
		nfp_abm_ctrl_set_q_act(alink, i, queue, act);
	पूर्ण
पूर्ण

अटल व्योम
nfp_abm_offload_compile_mq(काष्ठा nfp_abm_link *alink, काष्ठा nfp_qdisc *qdisc)
अणु
	अचिन्हित पूर्णांक i;

	qdisc->offload_mark = qdisc->type == NFP_QDISC_MQ;
	अगर (!qdisc->offload_mark)
		वापस;

	क्रम (i = 0; i < alink->total_queues; i++) अणु
		काष्ठा nfp_qdisc *child = qdisc->children[i];

		अगर (!nfp_abm_qdisc_child_valid(qdisc, i))
			जारी;

		nfp_abm_offload_compile_red(alink, child, i);
	पूर्ण
पूर्ण

व्योम nfp_abm_qdisc_offload_update(काष्ठा nfp_abm_link *alink)
अणु
	काष्ठा nfp_abm *abm = alink->abm;
	काष्ठा radix_tree_iter iter;
	काष्ठा nfp_qdisc *qdisc;
	व्योम __rcu **slot;
	माप_प्रकार i;

	/* Mark all thresholds as unconfigured */
	क्रम (i = 0; i < abm->num_bands; i++)
		__biपंचांगap_set(abm->threshold_undef,
			     i * NFP_NET_MAX_RX_RINGS + alink->queue_base,
			     alink->total_queues);

	/* Clear offload marks */
	radix_tree_क्रम_each_slot(slot, &alink->qdiscs, &iter, 0) अणु
		qdisc = nfp_abm_qdisc_tree_deref_slot(slot);
		qdisc->offload_mark = false;
	पूर्ण

	अगर (alink->root_qdisc)
		nfp_abm_offload_compile_mq(alink, alink->root_qdisc);

	/* Refresh offload status */
	radix_tree_क्रम_each_slot(slot, &alink->qdiscs, &iter, 0) अणु
		qdisc = nfp_abm_qdisc_tree_deref_slot(slot);
		अगर (!qdisc->offload_mark && qdisc->offloaded)
			nfp_abm_qdisc_offload_stop(alink, qdisc);
		qdisc->offloaded = qdisc->offload_mark;
	पूर्ण

	/* Reset the unconfigured thresholds */
	क्रम (i = 0; i < abm->num_thresholds; i++)
		अगर (test_bit(i, abm->threshold_undef))
			__nfp_abm_ctrl_set_q_lvl(abm, i, NFP_ABM_LVL_अनन्त);

	__nfp_abm_stats_update(alink, kसमय_get());
पूर्ण

अटल व्योम
nfp_abm_qdisc_clear_mq(काष्ठा net_device *netdev, काष्ठा nfp_abm_link *alink,
		       काष्ठा nfp_qdisc *qdisc)
अणु
	काष्ठा radix_tree_iter iter;
	अचिन्हित पूर्णांक mq_refs = 0;
	व्योम __rcu **slot;

	अगर (!qdisc->use_cnt)
		वापस;
	/* MQ करोesn't notअगरy well on deकाष्ठाion, we need special handling of
	 * MQ's children.
	 */
	अगर (qdisc->type == NFP_QDISC_MQ &&
	    qdisc == alink->root_qdisc &&
	    netdev->reg_state == NETREG_UNREGISTERING)
		वापस;

	/* Count refs held by MQ instances and clear poपूर्णांकers */
	radix_tree_क्रम_each_slot(slot, &alink->qdiscs, &iter, 0) अणु
		काष्ठा nfp_qdisc *mq = nfp_abm_qdisc_tree_deref_slot(slot);
		अचिन्हित पूर्णांक i;

		अगर (mq->type != NFP_QDISC_MQ || mq->netdev != netdev)
			जारी;
		क्रम (i = 0; i < mq->num_children; i++)
			अगर (mq->children[i] == qdisc) अणु
				mq->children[i] = शून्य;
				mq_refs++;
			पूर्ण
	पूर्ण

	WARN(qdisc->use_cnt != mq_refs, "non-zero qdisc use count: %d (- %d)\n",
	     qdisc->use_cnt, mq_refs);
पूर्ण

अटल व्योम
nfp_abm_qdisc_मुक्त(काष्ठा net_device *netdev, काष्ठा nfp_abm_link *alink,
		   काष्ठा nfp_qdisc *qdisc)
अणु
	काष्ठा nfp_port *port = nfp_port_from_netdev(netdev);

	अगर (!qdisc)
		वापस;
	nfp_abm_qdisc_clear_mq(netdev, alink, qdisc);
	WARN_ON(radix_tree_delete(&alink->qdiscs,
				  TC_H_MAJ(qdisc->handle)) != qdisc);

	kमुक्त(qdisc->children);
	kमुक्त(qdisc);

	port->tc_offload_cnt--;
पूर्ण

अटल काष्ठा nfp_qdisc *
nfp_abm_qdisc_alloc(काष्ठा net_device *netdev, काष्ठा nfp_abm_link *alink,
		    क्रमागत nfp_qdisc_type type, u32 parent_handle, u32 handle,
		    अचिन्हित पूर्णांक children)
अणु
	काष्ठा nfp_port *port = nfp_port_from_netdev(netdev);
	काष्ठा nfp_qdisc *qdisc;
	पूर्णांक err;

	qdisc = kzalloc(माप(*qdisc), GFP_KERNEL);
	अगर (!qdisc)
		वापस शून्य;

	अगर (children) अणु
		qdisc->children = kसुस्मृति(children, माप(व्योम *), GFP_KERNEL);
		अगर (!qdisc->children)
			जाओ err_मुक्त_qdisc;
	पूर्ण

	qdisc->netdev = netdev;
	qdisc->type = type;
	qdisc->parent_handle = parent_handle;
	qdisc->handle = handle;
	qdisc->num_children = children;

	err = radix_tree_insert(&alink->qdiscs, TC_H_MAJ(qdisc->handle), qdisc);
	अगर (err) अणु
		nfp_err(alink->abm->app->cpp,
			"Qdisc insertion into radix tree failed: %d\n", err);
		जाओ err_मुक्त_child_tbl;
	पूर्ण

	port->tc_offload_cnt++;
	वापस qdisc;

err_मुक्त_child_tbl:
	kमुक्त(qdisc->children);
err_मुक्त_qdisc:
	kमुक्त(qdisc);
	वापस शून्य;
पूर्ण

अटल काष्ठा nfp_qdisc *
nfp_abm_qdisc_find(काष्ठा nfp_abm_link *alink, u32 handle)
अणु
	वापस radix_tree_lookup(&alink->qdiscs, TC_H_MAJ(handle));
पूर्ण

अटल पूर्णांक
nfp_abm_qdisc_replace(काष्ठा net_device *netdev, काष्ठा nfp_abm_link *alink,
		      क्रमागत nfp_qdisc_type type, u32 parent_handle, u32 handle,
		      अचिन्हित पूर्णांक children, काष्ठा nfp_qdisc **qdisc)
अणु
	*qdisc = nfp_abm_qdisc_find(alink, handle);
	अगर (*qdisc) अणु
		अगर (WARN_ON((*qdisc)->type != type))
			वापस -EINVAL;
		वापस 1;
	पूर्ण

	*qdisc = nfp_abm_qdisc_alloc(netdev, alink, type, parent_handle, handle,
				     children);
	वापस *qdisc ? 0 : -ENOMEM;
पूर्ण

अटल व्योम
nfp_abm_qdisc_destroy(काष्ठा net_device *netdev, काष्ठा nfp_abm_link *alink,
		      u32 handle)
अणु
	काष्ठा nfp_qdisc *qdisc;

	qdisc = nfp_abm_qdisc_find(alink, handle);
	अगर (!qdisc)
		वापस;

	/* We करोn't get TC_SETUP_ROOT_QDISC w/ MQ when netdev is unरेजिस्टरed */
	अगर (alink->root_qdisc == qdisc)
		qdisc->use_cnt--;

	nfp_abm_qdisc_unlink_children(qdisc, 0, qdisc->num_children);
	nfp_abm_qdisc_मुक्त(netdev, alink, qdisc);

	अगर (alink->root_qdisc == qdisc) अणु
		alink->root_qdisc = शून्य;
		/* Only root change matters, other changes are acted upon on
		 * the graft notअगरication.
		 */
		nfp_abm_qdisc_offload_update(alink);
	पूर्ण
पूर्ण

अटल पूर्णांक
nfp_abm_qdisc_graft(काष्ठा nfp_abm_link *alink, u32 handle, u32 child_handle,
		    अचिन्हित पूर्णांक id)
अणु
	काष्ठा nfp_qdisc *parent, *child;

	parent = nfp_abm_qdisc_find(alink, handle);
	अगर (!parent)
		वापस 0;

	अगर (WARN(id >= parent->num_children,
		 "graft child out of bound %d >= %d\n",
		 id, parent->num_children))
		वापस -EINVAL;

	nfp_abm_qdisc_unlink_children(parent, id, id + 1);

	child = nfp_abm_qdisc_find(alink, child_handle);
	अगर (child)
		child->use_cnt++;
	अन्यथा
		child = NFP_QDISC_UNTRACKED;
	parent->children[id] = child;

	nfp_abm_qdisc_offload_update(alink);

	वापस 0;
पूर्ण

अटल व्योम
nfp_abm_stats_calculate(काष्ठा nfp_alink_stats *new,
			काष्ठा nfp_alink_stats *old,
			काष्ठा gnet_stats_basic_packed *bstats,
			काष्ठा gnet_stats_queue *qstats)
अणु
	_bstats_update(bstats, new->tx_bytes - old->tx_bytes,
		       new->tx_pkts - old->tx_pkts);
	qstats->qlen += new->backlog_pkts - old->backlog_pkts;
	qstats->backlog += new->backlog_bytes - old->backlog_bytes;
	qstats->overlimits += new->overlimits - old->overlimits;
	qstats->drops += new->drops - old->drops;
पूर्ण

अटल व्योम
nfp_abm_stats_red_calculate(काष्ठा nfp_alink_xstats *new,
			    काष्ठा nfp_alink_xstats *old,
			    काष्ठा red_stats *stats)
अणु
	stats->क्रमced_mark += new->ecn_marked - old->ecn_marked;
	stats->pdrop += new->pdrop - old->pdrop;
पूर्ण

अटल पूर्णांक
nfp_abm_gred_stats(काष्ठा nfp_abm_link *alink, u32 handle,
		   काष्ठा tc_gred_qopt_offload_stats *stats)
अणु
	काष्ठा nfp_qdisc *qdisc;
	अचिन्हित पूर्णांक i;

	nfp_abm_stats_update(alink);

	qdisc = nfp_abm_qdisc_find(alink, handle);
	अगर (!qdisc)
		वापस -EOPNOTSUPP;
	/* If the qdisc offload has stopped we may need to adjust the backlog
	 * counters back so carry on even अगर qdisc is not currently offloaded.
	 */

	क्रम (i = 0; i < qdisc->red.num_bands; i++) अणु
		अगर (!stats->xstats[i])
			जारी;

		nfp_abm_stats_calculate(&qdisc->red.band[i].stats,
					&qdisc->red.band[i].prev_stats,
					&stats->bstats[i], &stats->qstats[i]);
		qdisc->red.band[i].prev_stats = qdisc->red.band[i].stats;

		nfp_abm_stats_red_calculate(&qdisc->red.band[i].xstats,
					    &qdisc->red.band[i].prev_xstats,
					    stats->xstats[i]);
		qdisc->red.band[i].prev_xstats = qdisc->red.band[i].xstats;
	पूर्ण

	वापस qdisc->offloaded ? 0 : -EOPNOTSUPP;
पूर्ण

अटल bool
nfp_abm_gred_check_params(काष्ठा nfp_abm_link *alink,
			  काष्ठा tc_gred_qopt_offload *opt)
अणु
	काष्ठा nfp_cpp *cpp = alink->abm->app->cpp;
	काष्ठा nfp_abm *abm = alink->abm;
	अचिन्हित पूर्णांक i;

	अगर (opt->set.grio_on || opt->set.wred_on) अणु
		nfp_warn(cpp, "GRED offload failed - GRIO and WRED not supported (p:%08x h:%08x)\n",
			 opt->parent, opt->handle);
		वापस false;
	पूर्ण
	अगर (opt->set.dp_def != alink->def_band) अणु
		nfp_warn(cpp, "GRED offload failed - default band must be %d (p:%08x h:%08x)\n",
			 alink->def_band, opt->parent, opt->handle);
		वापस false;
	पूर्ण
	अगर (opt->set.dp_cnt != abm->num_bands) अणु
		nfp_warn(cpp, "GRED offload failed - band count must be %d (p:%08x h:%08x)\n",
			 abm->num_bands, opt->parent, opt->handle);
		वापस false;
	पूर्ण

	क्रम (i = 0; i < abm->num_bands; i++) अणु
		काष्ठा tc_gred_vq_qopt_offload_params *band = &opt->set.tab[i];

		अगर (!band->present)
			वापस false;
		अगर (!band->is_ecn && !nfp_abm_has_drop(abm)) अणु
			nfp_warn(cpp, "GRED offload failed - drop is not supported (ECN option required) (p:%08x h:%08x vq:%d)\n",
				 opt->parent, opt->handle, i);
			वापस false;
		पूर्ण
		अगर (band->is_ecn && !nfp_abm_has_mark(abm)) अणु
			nfp_warn(cpp, "GRED offload failed - ECN marking not supported (p:%08x h:%08x vq:%d)\n",
				 opt->parent, opt->handle, i);
			वापस false;
		पूर्ण
		अगर (band->is_harddrop) अणु
			nfp_warn(cpp, "GRED offload failed - harddrop is not supported (p:%08x h:%08x vq:%d)\n",
				 opt->parent, opt->handle, i);
			वापस false;
		पूर्ण
		अगर (band->min != band->max) अणु
			nfp_warn(cpp, "GRED offload failed - threshold mismatch (p:%08x h:%08x vq:%d)\n",
				 opt->parent, opt->handle, i);
			वापस false;
		पूर्ण
		अगर (band->min > S32_MAX) अणु
			nfp_warn(cpp, "GRED offload failed - threshold too large %d > %d (p:%08x h:%08x vq:%d)\n",
				 band->min, S32_MAX, opt->parent, opt->handle,
				 i);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक
nfp_abm_gred_replace(काष्ठा net_device *netdev, काष्ठा nfp_abm_link *alink,
		     काष्ठा tc_gred_qopt_offload *opt)
अणु
	काष्ठा nfp_qdisc *qdisc;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = nfp_abm_qdisc_replace(netdev, alink, NFP_QDISC_GRED, opt->parent,
				    opt->handle, 0, &qdisc);
	अगर (ret < 0)
		वापस ret;

	qdisc->params_ok = nfp_abm_gred_check_params(alink, opt);
	अगर (qdisc->params_ok) अणु
		qdisc->red.num_bands = opt->set.dp_cnt;
		क्रम (i = 0; i < qdisc->red.num_bands; i++) अणु
			qdisc->red.band[i].ecn = opt->set.tab[i].is_ecn;
			qdisc->red.band[i].threshold = opt->set.tab[i].min;
		पूर्ण
	पूर्ण

	अगर (qdisc->use_cnt)
		nfp_abm_qdisc_offload_update(alink);

	वापस 0;
पूर्ण

पूर्णांक nfp_abm_setup_tc_gred(काष्ठा net_device *netdev, काष्ठा nfp_abm_link *alink,
			  काष्ठा tc_gred_qopt_offload *opt)
अणु
	चयन (opt->command) अणु
	हाल TC_GRED_REPLACE:
		वापस nfp_abm_gred_replace(netdev, alink, opt);
	हाल TC_GRED_DESTROY:
		nfp_abm_qdisc_destroy(netdev, alink, opt->handle);
		वापस 0;
	हाल TC_GRED_STATS:
		वापस nfp_abm_gred_stats(alink, opt->handle, &opt->stats);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक
nfp_abm_red_xstats(काष्ठा nfp_abm_link *alink, काष्ठा tc_red_qopt_offload *opt)
अणु
	काष्ठा nfp_qdisc *qdisc;

	nfp_abm_stats_update(alink);

	qdisc = nfp_abm_qdisc_find(alink, opt->handle);
	अगर (!qdisc || !qdisc->offloaded)
		वापस -EOPNOTSUPP;

	nfp_abm_stats_red_calculate(&qdisc->red.band[0].xstats,
				    &qdisc->red.band[0].prev_xstats,
				    opt->xstats);
	qdisc->red.band[0].prev_xstats = qdisc->red.band[0].xstats;
	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_abm_red_stats(काष्ठा nfp_abm_link *alink, u32 handle,
		  काष्ठा tc_qopt_offload_stats *stats)
अणु
	काष्ठा nfp_qdisc *qdisc;

	nfp_abm_stats_update(alink);

	qdisc = nfp_abm_qdisc_find(alink, handle);
	अगर (!qdisc)
		वापस -EOPNOTSUPP;
	/* If the qdisc offload has stopped we may need to adjust the backlog
	 * counters back so carry on even अगर qdisc is not currently offloaded.
	 */

	nfp_abm_stats_calculate(&qdisc->red.band[0].stats,
				&qdisc->red.band[0].prev_stats,
				stats->bstats, stats->qstats);
	qdisc->red.band[0].prev_stats = qdisc->red.band[0].stats;

	वापस qdisc->offloaded ? 0 : -EOPNOTSUPP;
पूर्ण

अटल bool
nfp_abm_red_check_params(काष्ठा nfp_abm_link *alink,
			 काष्ठा tc_red_qopt_offload *opt)
अणु
	काष्ठा nfp_cpp *cpp = alink->abm->app->cpp;
	काष्ठा nfp_abm *abm = alink->abm;

	अगर (!opt->set.is_ecn && !nfp_abm_has_drop(abm)) अणु
		nfp_warn(cpp, "RED offload failed - drop is not supported (ECN option required) (p:%08x h:%08x)\n",
			 opt->parent, opt->handle);
		वापस false;
	पूर्ण
	अगर (opt->set.is_ecn && !nfp_abm_has_mark(abm)) अणु
		nfp_warn(cpp, "RED offload failed - ECN marking not supported (p:%08x h:%08x)\n",
			 opt->parent, opt->handle);
		वापस false;
	पूर्ण
	अगर (opt->set.is_harddrop) अणु
		nfp_warn(cpp, "RED offload failed - harddrop is not supported (p:%08x h:%08x)\n",
			 opt->parent, opt->handle);
		वापस false;
	पूर्ण
	अगर (opt->set.min != opt->set.max) अणु
		nfp_warn(cpp, "RED offload failed - unsupported min/max parameters (p:%08x h:%08x)\n",
			 opt->parent, opt->handle);
		वापस false;
	पूर्ण
	अगर (opt->set.min > NFP_ABM_LVL_अनन्त) अणु
		nfp_warn(cpp, "RED offload failed - threshold too large %d > %d (p:%08x h:%08x)\n",
			 opt->set.min, NFP_ABM_LVL_अनन्त, opt->parent,
			 opt->handle);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक
nfp_abm_red_replace(काष्ठा net_device *netdev, काष्ठा nfp_abm_link *alink,
		    काष्ठा tc_red_qopt_offload *opt)
अणु
	काष्ठा nfp_qdisc *qdisc;
	पूर्णांक ret;

	ret = nfp_abm_qdisc_replace(netdev, alink, NFP_QDISC_RED, opt->parent,
				    opt->handle, 1, &qdisc);
	अगर (ret < 0)
		वापस ret;

	/* If limit != 0 child माला_लो reset */
	अगर (opt->set.limit) अणु
		अगर (nfp_abm_qdisc_child_valid(qdisc, 0))
			qdisc->children[0]->use_cnt--;
		qdisc->children[0] = शून्य;
	पूर्ण अन्यथा अणु
		/* Qdisc was just allocated without a limit will use noop_qdisc,
		 * i.e. a block hole.
		 */
		अगर (!ret)
			qdisc->children[0] = NFP_QDISC_UNTRACKED;
	पूर्ण

	qdisc->params_ok = nfp_abm_red_check_params(alink, opt);
	अगर (qdisc->params_ok) अणु
		qdisc->red.num_bands = 1;
		qdisc->red.band[0].ecn = opt->set.is_ecn;
		qdisc->red.band[0].threshold = opt->set.min;
	पूर्ण

	अगर (qdisc->use_cnt == 1)
		nfp_abm_qdisc_offload_update(alink);

	वापस 0;
पूर्ण

पूर्णांक nfp_abm_setup_tc_red(काष्ठा net_device *netdev, काष्ठा nfp_abm_link *alink,
			 काष्ठा tc_red_qopt_offload *opt)
अणु
	चयन (opt->command) अणु
	हाल TC_RED_REPLACE:
		वापस nfp_abm_red_replace(netdev, alink, opt);
	हाल TC_RED_DESTROY:
		nfp_abm_qdisc_destroy(netdev, alink, opt->handle);
		वापस 0;
	हाल TC_RED_STATS:
		वापस nfp_abm_red_stats(alink, opt->handle, &opt->stats);
	हाल TC_RED_XSTATS:
		वापस nfp_abm_red_xstats(alink, opt);
	हाल TC_RED_GRAFT:
		वापस nfp_abm_qdisc_graft(alink, opt->handle,
					   opt->child_handle, 0);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक
nfp_abm_mq_create(काष्ठा net_device *netdev, काष्ठा nfp_abm_link *alink,
		  काष्ठा tc_mq_qopt_offload *opt)
अणु
	काष्ठा nfp_qdisc *qdisc;
	पूर्णांक ret;

	ret = nfp_abm_qdisc_replace(netdev, alink, NFP_QDISC_MQ,
				    TC_H_ROOT, opt->handle, alink->total_queues,
				    &qdisc);
	अगर (ret < 0)
		वापस ret;

	qdisc->params_ok = true;
	qdisc->offloaded = true;
	nfp_abm_qdisc_offload_update(alink);
	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_abm_mq_stats(काष्ठा nfp_abm_link *alink, u32 handle,
		 काष्ठा tc_qopt_offload_stats *stats)
अणु
	काष्ठा nfp_qdisc *qdisc, *red;
	अचिन्हित पूर्णांक i, j;

	qdisc = nfp_abm_qdisc_find(alink, handle);
	अगर (!qdisc)
		वापस -EOPNOTSUPP;

	nfp_abm_stats_update(alink);

	/* MQ stats are summed over the children in the core, so we need
	 * to add up the unreported child values.
	 */
	स_रखो(&qdisc->mq.stats, 0, माप(qdisc->mq.stats));
	स_रखो(&qdisc->mq.prev_stats, 0, माप(qdisc->mq.prev_stats));

	क्रम (i = 0; i < qdisc->num_children; i++) अणु
		अगर (!nfp_abm_qdisc_child_valid(qdisc, i))
			जारी;

		अगर (!nfp_abm_qdisc_is_red(qdisc->children[i]))
			जारी;
		red = qdisc->children[i];

		क्रम (j = 0; j < red->red.num_bands; j++) अणु
			nfp_abm_stats_propagate(&qdisc->mq.stats,
						&red->red.band[j].stats);
			nfp_abm_stats_propagate(&qdisc->mq.prev_stats,
						&red->red.band[j].prev_stats);
		पूर्ण
	पूर्ण

	nfp_abm_stats_calculate(&qdisc->mq.stats, &qdisc->mq.prev_stats,
				stats->bstats, stats->qstats);

	वापस qdisc->offloaded ? 0 : -EOPNOTSUPP;
पूर्ण

पूर्णांक nfp_abm_setup_tc_mq(काष्ठा net_device *netdev, काष्ठा nfp_abm_link *alink,
			काष्ठा tc_mq_qopt_offload *opt)
अणु
	चयन (opt->command) अणु
	हाल TC_MQ_CREATE:
		वापस nfp_abm_mq_create(netdev, alink, opt);
	हाल TC_MQ_DESTROY:
		nfp_abm_qdisc_destroy(netdev, alink, opt->handle);
		वापस 0;
	हाल TC_MQ_STATS:
		वापस nfp_abm_mq_stats(alink, opt->handle, &opt->stats);
	हाल TC_MQ_GRAFT:
		वापस nfp_abm_qdisc_graft(alink, opt->handle,
					   opt->graft_params.child_handle,
					   opt->graft_params.queue);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

पूर्णांक nfp_abm_setup_root(काष्ठा net_device *netdev, काष्ठा nfp_abm_link *alink,
		       काष्ठा tc_root_qopt_offload *opt)
अणु
	अगर (opt->ingress)
		वापस -EOPNOTSUPP;
	अगर (alink->root_qdisc)
		alink->root_qdisc->use_cnt--;
	alink->root_qdisc = nfp_abm_qdisc_find(alink, opt->handle);
	अगर (alink->root_qdisc)
		alink->root_qdisc->use_cnt++;

	nfp_abm_qdisc_offload_update(alink);

	वापस 0;
पूर्ण
