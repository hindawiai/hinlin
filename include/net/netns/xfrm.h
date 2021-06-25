<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NETNS_XFRM_H
#घोषणा __NETNS_XFRM_H

#समावेश <linux/list.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/rhashtable-types.h>
#समावेश <linux/xfrm.h>
#समावेश <net/dst_ops.h>

काष्ठा ctl_table_header;

काष्ठा xfrm_policy_hash अणु
	काष्ठा hlist_head	__rcu *table;
	अचिन्हित पूर्णांक		hmask;
	u8			dbits4;
	u8			sbits4;
	u8			dbits6;
	u8			sbits6;
पूर्ण;

काष्ठा xfrm_policy_hthresh अणु
	काष्ठा work_काष्ठा	work;
	seqlock_t		lock;
	u8			lbits4;
	u8			rbits4;
	u8			lbits6;
	u8			rbits6;
पूर्ण;

काष्ठा netns_xfrm अणु
	काष्ठा list_head	state_all;
	/*
	 * Hash table to find appropriate SA towards given target (endpoपूर्णांक of
	 * tunnel or destination of transport mode) allowed by selector.
	 *
	 * Main use is finding SA after policy selected tunnel or transport
	 * mode. Also, it can be used by ah/esp icmp error handler to find
	 * offending SA.
	 */
	काष्ठा hlist_head	__rcu *state_bydst;
	काष्ठा hlist_head	__rcu *state_bysrc;
	काष्ठा hlist_head	__rcu *state_byspi;
	अचिन्हित पूर्णांक		state_hmask;
	अचिन्हित पूर्णांक		state_num;
	काष्ठा work_काष्ठा	state_hash_work;

	काष्ठा list_head	policy_all;
	काष्ठा hlist_head	*policy_byidx;
	अचिन्हित पूर्णांक		policy_idx_hmask;
	काष्ठा hlist_head	policy_inexact[XFRM_POLICY_MAX];
	काष्ठा xfrm_policy_hash	policy_bydst[XFRM_POLICY_MAX];
	अचिन्हित पूर्णांक		policy_count[XFRM_POLICY_MAX * 2];
	काष्ठा work_काष्ठा	policy_hash_work;
	काष्ठा xfrm_policy_hthresh policy_hthresh;
	काष्ठा list_head	inexact_bins;


	काष्ठा sock		*nlsk;
	काष्ठा sock		*nlsk_stash;

	u32			sysctl_aevent_eसमय;
	u32			sysctl_aevent_rseqth;
	पूर्णांक			sysctl_larval_drop;
	u32			sysctl_acq_expires;
#अगर_घोषित CONFIG_SYSCTL
	काष्ठा ctl_table_header	*sysctl_hdr;
#पूर्ण_अगर

	काष्ठा dst_ops		xfrm4_dst_ops;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा dst_ops		xfrm6_dst_ops;
#पूर्ण_अगर
	spinlock_t		xfrm_state_lock;
	seqcount_spinlock_t	xfrm_state_hash_generation;

	spinlock_t xfrm_policy_lock;
	काष्ठा mutex xfrm_cfg_mutex;
पूर्ण;

#पूर्ण_अगर
