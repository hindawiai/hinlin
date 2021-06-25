<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2018 Netronome Systems, Inc. */

#अगर_अघोषित __NFP_ABM_H__
#घोषणा __NFP_ABM_H__ 1

#समावेश <linux/bits.h>
#समावेश <linux/list.h>
#समावेश <linux/radix-tree.h>
#समावेश <net/devlink.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/pkt_sched.h>

/* Dump of 64 PRIOs and 256 REDs seems to take 850us on Xeon v4 @ 2.20GHz;
 * 2.5ms / 400Hz seems more than sufficient क्रम stats resolution.
 */
#घोषणा NFP_ABM_STATS_REFRESH_IVAL	(2500 * 1000) /* ns */

#घोषणा NFP_ABM_LVL_अनन्त		S32_MAX

काष्ठा nfp_app;
काष्ठा nfp_net;

#घोषणा NFP_ABM_PORTID_TYPE	GENMASK(23, 16)
#घोषणा NFP_ABM_PORTID_ID	GENMASK(7, 0)

/* The possible actions अगर thresholds are exceeded */
क्रमागत nfp_abm_q_action अणु
	/* mark अगर ECN capable, otherwise drop */
	NFP_ABM_ACT_MARK_DROP		= 0,
	/* mark अगर ECN capable, otherwise जाओ QM */
	NFP_ABM_ACT_MARK_QUEUE		= 1,
	NFP_ABM_ACT_DROP		= 2,
	NFP_ABM_ACT_QUEUE		= 3,
	NFP_ABM_ACT_NOQUEUE		= 4,
पूर्ण;

/**
 * काष्ठा nfp_abm - ABM NIC app काष्ठाure
 * @app:	back poपूर्णांकer to nfp_app
 * @pf_id:	ID of our PF link
 *
 * @red_support:	is RED offload supported
 * @num_prios:	number of supported DSCP priorities
 * @num_bands:	number of supported DSCP priority bands
 * @action_mask:	biपंचांगask of supported actions
 *
 * @thresholds:		current threshold configuration
 * @threshold_undef:	biपंचांगap of thresholds which have not been set
 * @actions:		current FW action configuration
 * @num_thresholds:	number of @thresholds and bits in @threshold_undef
 *
 * @prio_map_len:	computed length of FW priority map (in bytes)
 * @dscp_mask:		mask FW will apply on DSCP field
 *
 * @eचयन_mode:	devlink eचयन mode, advanced functions only visible
 *			in चयनdev mode
 *
 * @q_lvls:	queue level control area
 * @qm_stats:	queue statistics symbol
 * @q_stats:	basic queue statistics (only in per-band हाल)
 */
काष्ठा nfp_abm अणु
	काष्ठा nfp_app *app;
	अचिन्हित पूर्णांक pf_id;

	अचिन्हित पूर्णांक red_support;
	अचिन्हित पूर्णांक num_prios;
	अचिन्हित पूर्णांक num_bands;
	अचिन्हित पूर्णांक action_mask;

	u32 *thresholds;
	अचिन्हित दीर्घ *threshold_undef;
	u8 *actions;
	माप_प्रकार num_thresholds;

	अचिन्हित पूर्णांक prio_map_len;
	u8 dscp_mask;

	क्रमागत devlink_eचयन_mode eचयन_mode;

	स्थिर काष्ठा nfp_rtsym *q_lvls;
	स्थिर काष्ठा nfp_rtsym *qm_stats;
	स्थिर काष्ठा nfp_rtsym *q_stats;
पूर्ण;

/**
 * काष्ठा nfp_alink_stats - ABM NIC statistics
 * @tx_pkts:		number of TXed packets
 * @tx_bytes:		number of TXed bytes
 * @backlog_pkts:	momentary backlog length (packets)
 * @backlog_bytes:	momentary backlog length (bytes)
 * @overlimits:		number of ECN marked TXed packets (accumulative)
 * @drops:		number of tail-dropped packets (accumulative)
 */
काष्ठा nfp_alink_stats अणु
	u64 tx_pkts;
	u64 tx_bytes;
	u64 backlog_pkts;
	u64 backlog_bytes;
	u64 overlimits;
	u64 drops;
पूर्ण;

/**
 * काष्ठा nfp_alink_xstats - extended ABM NIC statistics
 * @ecn_marked:		number of ECN marked TXed packets
 * @pdrop:		number of hard drops due to queue limit
 */
काष्ठा nfp_alink_xstats अणु
	u64 ecn_marked;
	u64 pdrop;
पूर्ण;

क्रमागत nfp_qdisc_type अणु
	NFP_QDISC_NONE = 0,
	NFP_QDISC_MQ,
	NFP_QDISC_RED,
	NFP_QDISC_GRED,
पूर्ण;

#घोषणा NFP_QDISC_UNTRACKED	((काष्ठा nfp_qdisc *)1UL)

/**
 * काष्ठा nfp_qdisc - tracked TC Qdisc
 * @netdev:		netdev on which Qdisc was created
 * @type:		Qdisc type
 * @handle:		handle of this Qdisc
 * @parent_handle:	handle of the parent (unreliable अगर Qdisc was grafted)
 * @use_cnt:		number of attachment poपूर्णांकs in the hierarchy
 * @num_children:	current size of the @children array
 * @children:		poपूर्णांकers to children
 *
 * @params_ok:		parameters of this Qdisc are OK क्रम offload
 * @offload_mark:	offload refresh state - selected क्रम offload
 * @offloaded:		Qdisc is currently offloaded to the HW
 *
 * @mq:			MQ Qdisc specअगरic parameters and state
 * @mq.stats:		current stats of the MQ Qdisc
 * @mq.prev_stats:	previously reported @mq.stats
 *
 * @red:		RED Qdisc specअगरic parameters and state
 * @red.num_bands:	Number of valid entries in the @red.band table
 * @red.band:		Per-band array of RED instances
 * @red.band.ecn:		ECN marking is enabled (rather than drop)
 * @red.band.threshold:		ECN marking threshold
 * @red.band.stats:		current stats of the RED Qdisc
 * @red.band.prev_stats:	previously reported @red.stats
 * @red.band.xstats:		extended stats क्रम RED - current
 * @red.band.prev_xstats:	extended stats क्रम RED - previously reported
 */
काष्ठा nfp_qdisc अणु
	काष्ठा net_device *netdev;
	क्रमागत nfp_qdisc_type type;
	u32 handle;
	u32 parent_handle;
	अचिन्हित पूर्णांक use_cnt;
	अचिन्हित पूर्णांक num_children;
	काष्ठा nfp_qdisc **children;

	bool params_ok;
	bool offload_mark;
	bool offloaded;

	जोड़ अणु
		/* NFP_QDISC_MQ */
		काष्ठा अणु
			काष्ठा nfp_alink_stats stats;
			काष्ठा nfp_alink_stats prev_stats;
		पूर्ण mq;
		/* TC_SETUP_QDISC_RED, TC_SETUP_QDISC_GRED */
		काष्ठा अणु
			अचिन्हित पूर्णांक num_bands;

			काष्ठा अणु
				bool ecn;
				u32 threshold;
				काष्ठा nfp_alink_stats stats;
				काष्ठा nfp_alink_stats prev_stats;
				काष्ठा nfp_alink_xstats xstats;
				काष्ठा nfp_alink_xstats prev_xstats;
			पूर्ण band[MAX_DPs];
		पूर्ण red;
	पूर्ण;
पूर्ण;

/**
 * काष्ठा nfp_abm_link - port tuple of a ABM NIC
 * @abm:	back poपूर्णांकer to nfp_abm
 * @vnic:	data vNIC
 * @id:		id of the data vNIC
 * @queue_base:	id of base to host queue within PCIe (not QC idx)
 * @total_queues:	number of PF queues
 *
 * @last_stats_update:	kसमय of last stats update
 *
 * @prio_map:		current map of priorities
 * @has_prio:		@prio_map is valid
 *
 * @def_band:		शेष band to use
 * @dscp_map:		list of DSCP to band mappings
 *
 * @root_qdisc:	poपूर्णांकer to the current root of the Qdisc hierarchy
 * @qdiscs:	all qdiscs recorded by major part of the handle
 */
काष्ठा nfp_abm_link अणु
	काष्ठा nfp_abm *abm;
	काष्ठा nfp_net *vnic;
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक queue_base;
	अचिन्हित पूर्णांक total_queues;

	u64 last_stats_update;

	u32 *prio_map;
	bool has_prio;

	u8 def_band;
	काष्ठा list_head dscp_map;

	काष्ठा nfp_qdisc *root_qdisc;
	काष्ठा radix_tree_root qdiscs;
पूर्ण;

अटल अंतरभूत bool nfp_abm_has_prio(काष्ठा nfp_abm *abm)
अणु
	वापस abm->num_bands > 1;
पूर्ण

अटल अंतरभूत bool nfp_abm_has_drop(काष्ठा nfp_abm *abm)
अणु
	वापस abm->action_mask & BIT(NFP_ABM_ACT_DROP);
पूर्ण

अटल अंतरभूत bool nfp_abm_has_mark(काष्ठा nfp_abm *abm)
अणु
	वापस abm->action_mask & BIT(NFP_ABM_ACT_MARK_DROP);
पूर्ण

व्योम nfp_abm_qdisc_offload_update(काष्ठा nfp_abm_link *alink);
पूर्णांक nfp_abm_setup_root(काष्ठा net_device *netdev, काष्ठा nfp_abm_link *alink,
		       काष्ठा tc_root_qopt_offload *opt);
पूर्णांक nfp_abm_setup_tc_red(काष्ठा net_device *netdev, काष्ठा nfp_abm_link *alink,
			 काष्ठा tc_red_qopt_offload *opt);
पूर्णांक nfp_abm_setup_tc_mq(काष्ठा net_device *netdev, काष्ठा nfp_abm_link *alink,
			काष्ठा tc_mq_qopt_offload *opt);
पूर्णांक nfp_abm_setup_tc_gred(काष्ठा net_device *netdev, काष्ठा nfp_abm_link *alink,
			  काष्ठा tc_gred_qopt_offload *opt);
पूर्णांक nfp_abm_setup_cls_block(काष्ठा net_device *netdev, काष्ठा nfp_repr *repr,
			    काष्ठा flow_block_offload *opt);

पूर्णांक nfp_abm_ctrl_पढ़ो_params(काष्ठा nfp_abm_link *alink);
पूर्णांक nfp_abm_ctrl_find_addrs(काष्ठा nfp_abm *abm);
पूर्णांक __nfp_abm_ctrl_set_q_lvl(काष्ठा nfp_abm *abm, अचिन्हित पूर्णांक id, u32 val);
पूर्णांक nfp_abm_ctrl_set_q_lvl(काष्ठा nfp_abm_link *alink, अचिन्हित पूर्णांक band,
			   अचिन्हित पूर्णांक queue, u32 val);
पूर्णांक __nfp_abm_ctrl_set_q_act(काष्ठा nfp_abm *abm, अचिन्हित पूर्णांक id,
			     क्रमागत nfp_abm_q_action act);
पूर्णांक nfp_abm_ctrl_set_q_act(काष्ठा nfp_abm_link *alink, अचिन्हित पूर्णांक band,
			   अचिन्हित पूर्णांक queue, क्रमागत nfp_abm_q_action act);
पूर्णांक nfp_abm_ctrl_पढ़ो_q_stats(काष्ठा nfp_abm_link *alink,
			      अचिन्हित पूर्णांक band, अचिन्हित पूर्णांक queue,
			      काष्ठा nfp_alink_stats *stats);
पूर्णांक nfp_abm_ctrl_पढ़ो_q_xstats(काष्ठा nfp_abm_link *alink,
			       अचिन्हित पूर्णांक band, अचिन्हित पूर्णांक queue,
			       काष्ठा nfp_alink_xstats *xstats);
u64 nfp_abm_ctrl_stat_non_sto(काष्ठा nfp_abm_link *alink, अचिन्हित पूर्णांक i);
u64 nfp_abm_ctrl_stat_sto(काष्ठा nfp_abm_link *alink, अचिन्हित पूर्णांक i);
पूर्णांक nfp_abm_ctrl_qm_enable(काष्ठा nfp_abm *abm);
पूर्णांक nfp_abm_ctrl_qm_disable(काष्ठा nfp_abm *abm);
व्योम nfp_abm_prio_map_update(काष्ठा nfp_abm *abm);
पूर्णांक nfp_abm_ctrl_prio_map_update(काष्ठा nfp_abm_link *alink, u32 *packed);
#पूर्ण_अगर
