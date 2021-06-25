<शैली गुरु>
/* bnx2x_sriov.h: QLogic Everest network driver.
 *
 * Copyright 2009-2013 Broadcom Corporation
 * Copyright 2014 QLogic Corporation
 * All rights reserved
 *
 * Unless you and QLogic execute a separate written software license
 * agreement governing use of this software, this software is licensed to you
 * under the terms of the GNU General Public License version 2, available
 * at http://www.gnu.org/licenses/old-licenses/gpl-2.0.hपंचांगl (the "GPL").
 *
 * Notwithstanding the above, under no circumstances may you combine this
 * software in any way with any other QLogic software provided under a
 * license other than the GPL, without QLogic's express prior written
 * consent.
 *
 * Maपूर्णांकained by: Ariel Elior <ariel.elior@qlogic.com>
 * Written by: Shmulik Ravid
 *	       Ariel Elior <ariel.elior@qlogic.com>
 */
#अगर_अघोषित BNX2X_SRIOV_H
#घोषणा BNX2X_SRIOV_H

#समावेश "bnx2x_vfpf.h"
#समावेश "bnx2x.h"

क्रमागत sample_bulletin_result अणु
	   PFVF_BULLETIN_UNCHANGED,
	   PFVF_BULLETIN_UPDATED,
	   PFVF_BULLETIN_CRC_ERR
पूर्ण;

#अगर_घोषित CONFIG_BNX2X_SRIOV

बाह्य काष्ठा workqueue_काष्ठा *bnx2x_iov_wq;

/* The bnx2x device काष्ठाure holds vfdb काष्ठाure described below.
 * The VF array is indexed by the relative vfid.
 */
#घोषणा BNX2X_VF_MAX_QUEUES		16
#घोषणा BNX2X_VF_MAX_TPA_AGG_QUEUES	8

काष्ठा bnx2x_sriov अणु
	u32 first_vf_in_pf;

	/* standard SRIOV capability fields, mostly क्रम debugging */
	पूर्णांक pos;		/* capability position */
	पूर्णांक nres;		/* number of resources */
	u32 cap;		/* SR-IOV Capabilities */
	u16 ctrl;		/* SR-IOV Control */
	u16 total;		/* total VFs associated with the PF */
	u16 initial;		/* initial VFs associated with the PF */
	u16 nr_virtfn;		/* number of VFs available */
	u16 offset;		/* first VF Routing ID offset */
	u16 stride;		/* following VF stride */
	u32 pgsz;		/* page size क्रम BAR alignment */
	u8 link;		/* Function Dependency Link */
पूर्ण;

/* bars */
काष्ठा bnx2x_vf_bar अणु
	u64 bar;
	u32 size;
पूर्ण;

काष्ठा bnx2x_vf_bar_info अणु
	काष्ठा bnx2x_vf_bar bars[PCI_SRIOV_NUM_BARS];
	u8 nr_bars;
पूर्ण;

/* vf queue (used both क्रम rx or tx) */
काष्ठा bnx2x_vf_queue अणु
	काष्ठा eth_context		*cxt;

	/* MACs object */
	काष्ठा bnx2x_vlan_mac_obj	mac_obj;

	/* VLANs object */
	काष्ठा bnx2x_vlan_mac_obj	vlan_obj;

	/* VLAN-MACs object */
	काष्ठा bnx2x_vlan_mac_obj	vlan_mac_obj;

	अचिन्हित दीर्घ accept_flags;	/* last accept flags configured */

	/* Queue Slow-path State object */
	काष्ठा bnx2x_queue_sp_obj	sp_obj;

	u32 cid;
	u16 index;
	u16 sb_idx;
	bool is_leading;
	bool sp_initialized;
पूर्ण;

/* काष्ठा bnx2x_vf_queue_स्थिरruct_params - prepare queue स्थिरruction
 * parameters: q-init, q-setup and SB index
 */
काष्ठा bnx2x_vf_queue_स्थिरruct_params अणु
	काष्ठा bnx2x_queue_state_params		qstate;
	काष्ठा bnx2x_queue_setup_params		prep_qsetup;
पूर्ण;

/* क्रमward */
काष्ठा bnx2x_virtf;

/* VFOP definitions */

काष्ठा bnx2x_vf_mac_vlan_filter अणु
	पूर्णांक type;
#घोषणा BNX2X_VF_FILTER_MAC	BIT(0)
#घोषणा BNX2X_VF_FILTER_VLAN	BIT(1)
#घोषणा BNX2X_VF_FILTER_VLAN_MAC \
	(BNX2X_VF_FILTER_MAC | BNX2X_VF_FILTER_VLAN) /*लघुcut*/

	bool add;
	bool applied;
	u8 *mac;
	u16 vid;
पूर्ण;

काष्ठा bnx2x_vf_mac_vlan_filters अणु
	पूर्णांक count;
	काष्ठा bnx2x_vf_mac_vlan_filter filters[];
पूर्ण;

/* vf context */
काष्ठा bnx2x_virtf अणु
	u16 cfg_flags;
#घोषणा VF_CFG_STATS_COALESCE	0x1
#घोषणा VF_CFG_EXT_BULLETIN	0x2
#घोषणा VF_CFG_VLAN_FILTER	0x4
	u8 link_cfg;		/* IFLA_VF_LINK_STATE_AUTO
				 * IFLA_VF_LINK_STATE_ENABLE
				 * IFLA_VF_LINK_STATE_DISABLE
				 */
	u8 state;
#घोषणा VF_FREE		0	/* VF पढ़ोy to be acquired holds no resc */
#घोषणा VF_ACQUIRED	1	/* VF acquired, but not initialized */
#घोषणा VF_ENABLED	2	/* VF Enabled */
#घोषणा VF_RESET	3	/* VF FLR'd, pending cleanup */
#घोषणा VF_LOST		4	/* Recovery जबतक VFs are loaded */

	bool flr_clnup_stage;	/* true during flr cleanup */
	bool malicious;		/* true अगर FW indicated so, until FLR */
	/* 1(true) अगर spoof check is enabled */
	u8 spoofchk;

	/* dma */
	dma_addr_t fw_stat_map;
	u16 stats_stride;
	dma_addr_t bulletin_map;

	/* Allocated resources counters. Beक्रमe the VF is acquired, the
	 * counters hold the following values:
	 *
	 * - xxq_count = 0 as the queues memory is not allocated yet.
	 *
	 * - sb_count  = The number of status blocks configured क्रम this VF in
	 *		 the IGU CAM. Initially पढ़ो during probe.
	 *
	 * - xx_rules_count = The number of rules अटलally and equally
	 *		      allocated क्रम each VF, during PF load.
	 */
	काष्ठा vf_pf_resc_request	alloc_resc;
#घोषणा vf_rxq_count(vf)		((vf)->alloc_resc.num_rxqs)
#घोषणा vf_txq_count(vf)		((vf)->alloc_resc.num_txqs)
#घोषणा vf_sb_count(vf)			((vf)->alloc_resc.num_sbs)
#घोषणा vf_mac_rules_cnt(vf)		((vf)->alloc_resc.num_mac_filters)
#घोषणा vf_vlan_rules_cnt(vf)		((vf)->alloc_resc.num_vlan_filters)
#घोषणा vf_mc_rules_cnt(vf)		((vf)->alloc_resc.num_mc_filters)

	u8 sb_count;	/* actual number of SBs */
	u8 igu_base_id;	/* base igu status block id */

	काष्ठा bnx2x_vf_queue	*vfqs;
#घोषणा LEADING_IDX			0
#घोषणा bnx2x_vfq_is_leading(vfq)	((vfq)->index == LEADING_IDX)
#घोषणा bnx2x_vfq(vf, nr, var)		((vf)->vfqs[(nr)].var)
#घोषणा bnx2x_leading_vfq(vf, var)	((vf)->vfqs[LEADING_IDX].var)

	u8 index;	/* index in the vf array */
	u8 असल_vfid;
	u8 sp_cl_id;
	u32 error;	/* 0 means all's-well */

	/* BDF */
	अचिन्हित पूर्णांक करोमुख्य;
	अचिन्हित पूर्णांक bus;
	अचिन्हित पूर्णांक devfn;

	/* bars */
	काष्ठा bnx2x_vf_bar bars[PCI_SRIOV_NUM_BARS];

	/* set-mac ramrod state 1-pending, 0-करोne */
	अचिन्हित दीर्घ	filter_state;

	/* leading rss client id ~~ the client id of the first rxq, must be
	 * set क्रम each txq.
	 */
	पूर्णांक leading_rss;

	/* MCAST object */
	काष्ठा bnx2x_mcast_obj		mcast_obj;

	/* RSS configuration object */
	काष्ठा bnx2x_rss_config_obj     rss_conf_obj;

	/* slow-path operations */
	काष्ठा mutex			op_mutex; /* one vfop at a समय mutex */
	क्रमागत channel_tlvs		op_current;

	u8 fp_hsi;

	काष्ठा bnx2x_credit_pool_obj	vf_vlans_pool;
	काष्ठा bnx2x_credit_pool_obj	vf_macs_pool;
पूर्ण;

#घोषणा BNX2X_NR_VIRTFN(bp)	((bp)->vfdb->sriov.nr_virtfn)

#घोषणा क्रम_each_vf(bp, var) \
		क्रम ((var) = 0; (var) < BNX2X_NR_VIRTFN(bp); (var)++)

#घोषणा क्रम_each_vfq(vf, var) \
		क्रम ((var) = 0; (var) < vf_rxq_count(vf); (var)++)

#घोषणा क्रम_each_vf_sb(vf, var) \
		क्रम ((var) = 0; (var) < vf_sb_count(vf); (var)++)

#घोषणा is_vf_multi(vf)	(vf_rxq_count(vf) > 1)

#घोषणा HW_VF_HANDLE(bp, असल_vfid) \
	(u16)(BP_ABS_FUNC((bp)) | (1<<3) |  ((u16)(असल_vfid) << 4))

#घोषणा FW_PF_MAX_HANDLE	8

#घोषणा FW_VF_HANDLE(असल_vfid)	\
	(असल_vfid + FW_PF_MAX_HANDLE)

#घोषणा GET_NUM_VFS_PER_PATH(bp)	64 /* use max possible value */
#घोषणा GET_NUM_VFS_PER_PF(bp)		((bp)->vfdb ? (bp)->vfdb->sriov.total \
						    : 0)
#घोषणा VF_MAC_CREDIT_CNT		1
#घोषणा VF_VLAN_CREDIT_CNT		2 /* VLAN0 + 'real' VLAN */

/* locking and unlocking the channel mutex */
व्योम bnx2x_lock_vf_pf_channel(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
			      क्रमागत channel_tlvs tlv);

व्योम bnx2x_unlock_vf_pf_channel(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
				क्रमागत channel_tlvs expected_tlv);

/* VF mail box (aka vf-pf channel) */

/* a container क्रम the bi-directional vf<-->pf messages.
 *  The actual response will be placed according to the offset parameter
 *  provided in the request
 */

#घोषणा MBX_MSG_ALIGN	8
#घोषणा MBX_MSG_ALIGNED_SIZE	(roundup(माप(काष्ठा bnx2x_vf_mbx_msg), \
				MBX_MSG_ALIGN))

काष्ठा bnx2x_vf_mbx_msg अणु
	जोड़ vfpf_tlvs req;
	जोड़ pfvf_tlvs resp;
पूर्ण;

काष्ठा bnx2x_vf_mbx अणु
	काष्ठा bnx2x_vf_mbx_msg *msg;
	dma_addr_t msg_mapping;

	/* VF GPA address */
	u32 vf_addr_lo;
	u32 vf_addr_hi;

	काष्ठा vfpf_first_tlv first_tlv;	/* saved VF request header */
पूर्ण;

काष्ठा bnx2x_vf_sp अणु
	जोड़ अणु
		काष्ठा eth_classअगरy_rules_ramrod_data	e2;
	पूर्ण mac_rdata;

	जोड़ अणु
		काष्ठा eth_classअगरy_rules_ramrod_data	e2;
	पूर्ण vlan_rdata;

	जोड़ अणु
		काष्ठा eth_classअगरy_rules_ramrod_data	e2;
	पूर्ण vlan_mac_rdata;

	जोड़ अणु
		काष्ठा eth_filter_rules_ramrod_data	e2;
	पूर्ण rx_mode_rdata;

	जोड़ अणु
		काष्ठा eth_multicast_rules_ramrod_data  e2;
	पूर्ण mcast_rdata;

	जोड़ अणु
		काष्ठा client_init_ramrod_data  init_data;
		काष्ठा client_update_ramrod_data update_data;
	पूर्ण q_data;

	जोड़ अणु
		काष्ठा eth_rss_update_ramrod_data e2;
	पूर्ण rss_rdata;
पूर्ण;

काष्ठा hw_dma अणु
	व्योम *addr;
	dma_addr_t mapping;
	माप_प्रकार size;
पूर्ण;

काष्ठा bnx2x_vfdb अणु
#घोषणा BP_VFDB(bp)		((bp)->vfdb)
	/* vf array */
	काष्ठा bnx2x_virtf	*vfs;
#घोषणा BP_VF(bp, idx)		((BP_VFDB(bp) && (bp)->vfdb->vfs) ? \
					&((bp)->vfdb->vfs[idx]) : शून्य)
#घोषणा bnx2x_vf(bp, idx, var)	((bp)->vfdb->vfs[idx].var)

	/* queue array - क्रम all vfs */
	काष्ठा bnx2x_vf_queue *vfqs;

	/* vf HW contexts */
	काष्ठा hw_dma		context[BNX2X_VF_CIDS/ILT_PAGE_CIDS];
#घोषणा	BP_VF_CXT_PAGE(bp, i)	(&(bp)->vfdb->context[i])

	/* SR-IOV inक्रमmation */
	काष्ठा bnx2x_sriov	sriov;
	काष्ठा hw_dma		mbx_dma;
#घोषणा BP_VF_MBX_DMA(bp)	(&((bp)->vfdb->mbx_dma))
	काष्ठा bnx2x_vf_mbx	mbxs[BNX2X_MAX_NUM_OF_VFS];
#घोषणा BP_VF_MBX(bp, vfid)	(&((bp)->vfdb->mbxs[vfid]))

	काष्ठा hw_dma		bulletin_dma;
#घोषणा BP_VF_BULLETIN_DMA(bp)	(&((bp)->vfdb->bulletin_dma))
#घोषणा	BP_VF_BULLETIN(bp, vf) \
	(((काष्ठा pf_vf_bulletin_content *)(BP_VF_BULLETIN_DMA(bp)->addr)) \
	 + (vf))

	काष्ठा hw_dma		sp_dma;
#घोषणा bnx2x_vf_sp(bp, vf, field) ((bp)->vfdb->sp_dma.addr +		\
		(vf)->index * माप(काष्ठा bnx2x_vf_sp) +		\
		दुरत्व(काष्ठा bnx2x_vf_sp, field))
#घोषणा bnx2x_vf_sp_map(bp, vf, field) ((bp)->vfdb->sp_dma.mapping +	\
		(vf)->index * माप(काष्ठा bnx2x_vf_sp) +		\
		दुरत्व(काष्ठा bnx2x_vf_sp, field))

#घोषणा FLRD_VFS_DWORDS (BNX2X_MAX_NUM_OF_VFS / 32)
	u32 flrd_vfs[FLRD_VFS_DWORDS];

	/* the number of msix vectors beदीर्घing to this PF designated क्रम VFs */
	u16 vf_sbs_pool;
	u16 first_vf_igu_entry;

	/* sp_rtnl synchronization */
	काष्ठा mutex			event_mutex;
	u64				event_occur;

	/* bulletin board update synchronization */
	काष्ठा mutex			bulletin_mutex;
पूर्ण;

/* queue access */
अटल अंतरभूत काष्ठा bnx2x_vf_queue *vfq_get(काष्ठा bnx2x_virtf *vf, u8 index)
अणु
	वापस &(vf->vfqs[index]);
पूर्ण

/* FW ids */
अटल अंतरभूत u8 vf_igu_sb(काष्ठा bnx2x_virtf *vf, u16 sb_idx)
अणु
	वापस vf->igu_base_id + sb_idx;
पूर्ण

अटल अंतरभूत u8 vf_hc_qzone(काष्ठा bnx2x_virtf *vf, u16 sb_idx)
अणु
	वापस vf_igu_sb(vf, sb_idx);
पूर्ण

अटल u8 vfq_cl_id(काष्ठा bnx2x_virtf *vf, काष्ठा bnx2x_vf_queue *q)
अणु
	वापस vf->igu_base_id + q->index;
पूर्ण

अटल अंतरभूत u8 vfq_stat_id(काष्ठा bnx2x_virtf *vf, काष्ठा bnx2x_vf_queue *q)
अणु
	अगर (vf->cfg_flags & VF_CFG_STATS_COALESCE)
		वापस vf->leading_rss;
	अन्यथा
		वापस vfq_cl_id(vf, q);
पूर्ण

अटल अंतरभूत u8 vfq_qzone_id(काष्ठा bnx2x_virtf *vf, काष्ठा bnx2x_vf_queue *q)
अणु
	वापस vfq_cl_id(vf, q);
पूर्ण

/* global iov routines */
पूर्णांक bnx2x_iov_init_ilt(काष्ठा bnx2x *bp, u16 line);
पूर्णांक bnx2x_iov_init_one(काष्ठा bnx2x *bp, पूर्णांक पूर्णांक_mode_param, पूर्णांक num_vfs_param);
व्योम bnx2x_iov_हटाओ_one(काष्ठा bnx2x *bp);
व्योम bnx2x_iov_मुक्त_mem(काष्ठा bnx2x *bp);
पूर्णांक bnx2x_iov_alloc_mem(काष्ठा bnx2x *bp);
पूर्णांक bnx2x_iov_nic_init(काष्ठा bnx2x *bp);
पूर्णांक bnx2x_iov_chip_cleanup(काष्ठा bnx2x *bp);
व्योम bnx2x_iov_init_dq(काष्ठा bnx2x *bp);
व्योम bnx2x_iov_init_dmae(काष्ठा bnx2x *bp);
व्योम bnx2x_iov_set_queue_sp_obj(काष्ठा bnx2x *bp, पूर्णांक vf_cid,
				काष्ठा bnx2x_queue_sp_obj **q_obj);
पूर्णांक bnx2x_iov_eq_sp_event(काष्ठा bnx2x *bp, जोड़ event_ring_elem *elem);
व्योम bnx2x_iov_adjust_stats_req(काष्ठा bnx2x *bp);
व्योम bnx2x_iov_storm_stats_update(काष्ठा bnx2x *bp);
/* global vf mailbox routines */
व्योम bnx2x_vf_mbx(काष्ठा bnx2x *bp);
व्योम bnx2x_vf_mbx_schedule(काष्ठा bnx2x *bp,
			   काष्ठा vf_pf_event_data *vfpf_event);
व्योम bnx2x_vf_enable_mbx(काष्ठा bnx2x *bp, u8 असल_vfid);

/* CORE VF API */
प्रकार u8 bnx2x_mac_addr_t[ETH_ALEN];

/* acquire */
पूर्णांक bnx2x_vf_acquire(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
		     काष्ठा vf_pf_resc_request *resc);
/* init */
पूर्णांक bnx2x_vf_init(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
		  dma_addr_t *sb_map);

/* VFOP queue स्थिरruction helpers */
व्योम bnx2x_vfop_qctor_dump_tx(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
			    काष्ठा bnx2x_queue_init_params *init_params,
			    काष्ठा bnx2x_queue_setup_params *setup_params,
			    u16 q_idx, u16 sb_idx);

व्योम bnx2x_vfop_qctor_dump_rx(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
			    काष्ठा bnx2x_queue_init_params *init_params,
			    काष्ठा bnx2x_queue_setup_params *setup_params,
			    u16 q_idx, u16 sb_idx);

व्योम bnx2x_vfop_qctor_prep(काष्ठा bnx2x *bp,
			   काष्ठा bnx2x_virtf *vf,
			   काष्ठा bnx2x_vf_queue *q,
			   काष्ठा bnx2x_vf_queue_स्थिरruct_params *p,
			   अचिन्हित दीर्घ q_type);

पूर्णांक bnx2x_vf_mac_vlan_config_list(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
				  काष्ठा bnx2x_vf_mac_vlan_filters *filters,
				  पूर्णांक qid, bool drv_only);

पूर्णांक bnx2x_vf_queue_setup(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf, पूर्णांक qid,
			 काष्ठा bnx2x_vf_queue_स्थिरruct_params *qctor);

पूर्णांक bnx2x_vf_queue_tearकरोwn(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf, पूर्णांक qid);

पूर्णांक bnx2x_vf_mcast(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
		   bnx2x_mac_addr_t *mcasts, पूर्णांक mc_num, bool drv_only);

पूर्णांक bnx2x_vf_rxmode(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
		    पूर्णांक qid, अचिन्हित दीर्घ accept_flags);

पूर्णांक bnx2x_vf_बंद(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf);

पूर्णांक bnx2x_vf_मुक्त(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf);

पूर्णांक bnx2x_vf_rss_update(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
			काष्ठा bnx2x_config_rss_params *rss);

पूर्णांक bnx2x_vf_tpa_update(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf,
			काष्ठा vfpf_tpa_tlv *tlv,
			काष्ठा bnx2x_queue_update_tpa_params *params);

/* VF release ~ VF बंद + VF release-resources
 *
 * Release is the ultimate SW shutकरोwn and is called whenever an
 * irrecoverable error is encountered.
 */
पूर्णांक bnx2x_vf_release(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf);
पूर्णांक bnx2x_vf_idx_by_असल_fid(काष्ठा bnx2x *bp, u16 असल_vfid);
u8 bnx2x_vf_max_queue_cnt(काष्ठा bnx2x *bp, काष्ठा bnx2x_virtf *vf);

/* FLR routines */

/* VF FLR helpers */
पूर्णांक bnx2x_vf_flr_clnup_epilog(काष्ठा bnx2x *bp, u8 असल_vfid);
व्योम bnx2x_vf_enable_access(काष्ठा bnx2x *bp, u8 असल_vfid);

/* Handles an FLR (or VF_DISABLE) notअगरication क्रमm the MCP */
व्योम bnx2x_vf_handle_flr_event(काष्ठा bnx2x *bp);

bool bnx2x_tlv_supported(u16 tlvtype);

u32 bnx2x_crc_vf_bulletin(काष्ठा pf_vf_bulletin_content *bulletin);
पूर्णांक bnx2x_post_vf_bulletin(काष्ठा bnx2x *bp, पूर्णांक vf);
व्योम bnx2x_vf_bulletin_finalize(काष्ठा pf_vf_bulletin_content *bulletin,
				bool support_दीर्घ);

क्रमागत sample_bulletin_result bnx2x_sample_bulletin(काष्ठा bnx2x *bp);

/* VF side vfpf channel functions */
पूर्णांक bnx2x_vfpf_acquire(काष्ठा bnx2x *bp, u8 tx_count, u8 rx_count);
पूर्णांक bnx2x_vfpf_release(काष्ठा bnx2x *bp);
पूर्णांक bnx2x_vfpf_release(काष्ठा bnx2x *bp);
पूर्णांक bnx2x_vfpf_init(काष्ठा bnx2x *bp);
व्योम bnx2x_vfpf_बंद_vf(काष्ठा bnx2x *bp);
पूर्णांक bnx2x_vfpf_setup_q(काष्ठा bnx2x *bp, काष्ठा bnx2x_fastpath *fp,
		       bool is_leading);
पूर्णांक bnx2x_vfpf_config_mac(काष्ठा bnx2x *bp, u8 *addr, u8 vf_qid, bool set);
पूर्णांक bnx2x_vfpf_config_rss(काष्ठा bnx2x *bp,
			  काष्ठा bnx2x_config_rss_params *params);
पूर्णांक bnx2x_vfpf_set_mcast(काष्ठा net_device *dev);
पूर्णांक bnx2x_vfpf_storm_rx_mode(काष्ठा bnx2x *bp);

अटल अंतरभूत व्योम bnx2x_vf_fill_fw_str(काष्ठा bnx2x *bp, अक्षर *buf,
					माप_प्रकार buf_len)
अणु
	strlcpy(buf, bp->acquire_resp.pfdev_info.fw_ver, buf_len);
पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_vf_ustorm_prods_offset(काष्ठा bnx2x *bp,
					       काष्ठा bnx2x_fastpath *fp)
अणु
	वापस PXP_VF_ADDR_USDM_QUEUES_START +
		bp->acquire_resp.resc.hw_qid[fp->index] *
		माप(काष्ठा ustorm_queue_zone_data);
पूर्ण

क्रमागत sample_bulletin_result bnx2x_sample_bulletin(काष्ठा bnx2x *bp);
व्योम bnx2x_समयr_sriov(काष्ठा bnx2x *bp);
व्योम __iomem *bnx2x_vf_करोorbells(काष्ठा bnx2x *bp);
व्योम bnx2x_vf_pci_dealloc(काष्ठा bnx2x *bp);
पूर्णांक bnx2x_vf_pci_alloc(काष्ठा bnx2x *bp);
पूर्णांक bnx2x_enable_sriov(काष्ठा bnx2x *bp);
व्योम bnx2x_disable_sriov(काष्ठा bnx2x *bp);
अटल अंतरभूत पूर्णांक bnx2x_vf_headroom(काष्ठा bnx2x *bp)
अणु
	वापस bp->vfdb->sriov.nr_virtfn * BNX2X_CIDS_PER_VF;
पूर्ण
व्योम bnx2x_pf_set_vfs_vlan(काष्ठा bnx2x *bp);
पूर्णांक bnx2x_sriov_configure(काष्ठा pci_dev *dev, पूर्णांक num_vfs);
व्योम bnx2x_iov_channel_करोwn(काष्ठा bnx2x *bp);

व्योम bnx2x_iov_task(काष्ठा work_काष्ठा *work);

व्योम bnx2x_schedule_iov_task(काष्ठा bnx2x *bp, क्रमागत bnx2x_iov_flag flag);

व्योम bnx2x_iov_link_update(काष्ठा bnx2x *bp);
पूर्णांक bnx2x_iov_link_update_vf(काष्ठा bnx2x *bp, पूर्णांक idx);

पूर्णांक bnx2x_set_vf_link_state(काष्ठा net_device *dev, पूर्णांक vf, पूर्णांक link_state);

पूर्णांक bnx2x_vfpf_update_vlan(काष्ठा bnx2x *bp, u16 vid, u8 vf_qid, bool add);
#अन्यथा /* CONFIG_BNX2X_SRIOV */

#घोषणा GET_NUM_VFS_PER_PATH(bp)	0
#घोषणा GET_NUM_VFS_PER_PF(bp)		0
#घोषणा VF_MAC_CREDIT_CNT		0
#घोषणा VF_VLAN_CREDIT_CNT		0

अटल अंतरभूत व्योम bnx2x_iov_set_queue_sp_obj(काष्ठा bnx2x *bp, पूर्णांक vf_cid,
				काष्ठा bnx2x_queue_sp_obj **q_obj) अणुपूर्ण
अटल अंतरभूत व्योम bnx2x_vf_handle_flr_event(काष्ठा bnx2x *bp) अणुपूर्ण
अटल अंतरभूत पूर्णांक bnx2x_iov_eq_sp_event(काष्ठा bnx2x *bp,
					जोड़ event_ring_elem *elem) अणुवापस 1; पूर्ण
अटल अंतरभूत व्योम bnx2x_vf_mbx(काष्ठा bnx2x *bp) अणुपूर्ण
अटल अंतरभूत व्योम bnx2x_vf_mbx_schedule(काष्ठा bnx2x *bp,
					 काष्ठा vf_pf_event_data *vfpf_event) अणुपूर्ण
अटल अंतरभूत पूर्णांक bnx2x_iov_init_ilt(काष्ठा bnx2x *bp, u16 line) अणुवापस line; पूर्ण
अटल अंतरभूत व्योम bnx2x_iov_init_dq(काष्ठा bnx2x *bp) अणुपूर्ण
अटल अंतरभूत पूर्णांक bnx2x_iov_alloc_mem(काष्ठा bnx2x *bp) अणुवापस 0; पूर्ण
अटल अंतरभूत व्योम bnx2x_iov_मुक्त_mem(काष्ठा bnx2x *bp) अणुपूर्ण
अटल अंतरभूत पूर्णांक bnx2x_iov_chip_cleanup(काष्ठा bnx2x *bp) अणुवापस 0; पूर्ण
अटल अंतरभूत व्योम bnx2x_iov_init_dmae(काष्ठा bnx2x *bp) अणुपूर्ण
अटल अंतरभूत पूर्णांक bnx2x_iov_init_one(काष्ठा bnx2x *bp, पूर्णांक पूर्णांक_mode_param,
				     पूर्णांक num_vfs_param) अणुवापस 0; पूर्ण
अटल अंतरभूत व्योम bnx2x_iov_हटाओ_one(काष्ठा bnx2x *bp) अणुपूर्ण
अटल अंतरभूत पूर्णांक bnx2x_enable_sriov(काष्ठा bnx2x *bp) अणुवापस 0; पूर्ण
अटल अंतरभूत व्योम bnx2x_disable_sriov(काष्ठा bnx2x *bp) अणुपूर्ण
अटल अंतरभूत पूर्णांक bnx2x_vfpf_acquire(काष्ठा bnx2x *bp,
				     u8 tx_count, u8 rx_count) अणुवापस 0; पूर्ण
अटल अंतरभूत पूर्णांक bnx2x_vfpf_release(काष्ठा bnx2x *bp) अणुवापस 0; पूर्ण
अटल अंतरभूत पूर्णांक bnx2x_vfpf_init(काष्ठा bnx2x *bp) अणुवापस 0; पूर्ण
अटल अंतरभूत व्योम bnx2x_vfpf_बंद_vf(काष्ठा bnx2x *bp) अणुपूर्ण
अटल अंतरभूत पूर्णांक bnx2x_vfpf_setup_q(काष्ठा bnx2x *bp, काष्ठा bnx2x_fastpath *fp, bool is_leading) अणुवापस 0; पूर्ण
अटल अंतरभूत पूर्णांक bnx2x_vfpf_config_mac(काष्ठा bnx2x *bp, u8 *addr,
					u8 vf_qid, bool set) अणुवापस 0; पूर्ण
अटल अंतरभूत पूर्णांक bnx2x_vfpf_config_rss(काष्ठा bnx2x *bp,
					काष्ठा bnx2x_config_rss_params *params) अणुवापस 0; पूर्ण
अटल अंतरभूत पूर्णांक bnx2x_vfpf_set_mcast(काष्ठा net_device *dev) अणुवापस 0; पूर्ण
अटल अंतरभूत पूर्णांक bnx2x_vfpf_storm_rx_mode(काष्ठा bnx2x *bp) अणुवापस 0; पूर्ण
अटल अंतरभूत पूर्णांक bnx2x_iov_nic_init(काष्ठा bnx2x *bp) अणुवापस 0; पूर्ण
अटल अंतरभूत पूर्णांक bnx2x_vf_headroom(काष्ठा bnx2x *bp) अणुवापस 0; पूर्ण
अटल अंतरभूत व्योम bnx2x_iov_adjust_stats_req(काष्ठा bnx2x *bp) अणुपूर्ण
अटल अंतरभूत व्योम bnx2x_vf_fill_fw_str(काष्ठा bnx2x *bp, अक्षर *buf,
					माप_प्रकार buf_len) अणुपूर्ण
अटल अंतरभूत पूर्णांक bnx2x_vf_ustorm_prods_offset(काष्ठा bnx2x *bp,
					       काष्ठा bnx2x_fastpath *fp) अणुवापस 0; पूर्ण
अटल अंतरभूत क्रमागत sample_bulletin_result bnx2x_sample_bulletin(काष्ठा bnx2x *bp)
अणु
	वापस PFVF_BULLETIN_UNCHANGED;
पूर्ण
अटल अंतरभूत व्योम bnx2x_समयr_sriov(काष्ठा bnx2x *bp) अणुपूर्ण

अटल अंतरभूत व्योम __iomem *bnx2x_vf_करोorbells(काष्ठा bnx2x *bp)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम bnx2x_vf_pci_dealloc(काष्ठा bnx2x *bp) अणुपूर्ण
अटल अंतरभूत पूर्णांक bnx2x_vf_pci_alloc(काष्ठा bnx2x *bp) अणुवापस 0; पूर्ण
अटल अंतरभूत व्योम bnx2x_pf_set_vfs_vlan(काष्ठा bnx2x *bp) अणुपूर्ण
अटल अंतरभूत पूर्णांक bnx2x_sriov_configure(काष्ठा pci_dev *dev, पूर्णांक num_vfs) अणुवापस 0; पूर्ण
अटल अंतरभूत व्योम bnx2x_iov_channel_करोwn(काष्ठा bnx2x *bp) अणुपूर्ण

अटल अंतरभूत व्योम bnx2x_iov_task(काष्ठा work_काष्ठा *work) अणुपूर्ण
अटल अंतरभूत व्योम bnx2x_schedule_iov_task(काष्ठा bnx2x *bp, क्रमागत bnx2x_iov_flag flag) अणुपूर्ण
अटल अंतरभूत व्योम bnx2x_iov_link_update(काष्ठा bnx2x *bp) अणुपूर्ण
अटल अंतरभूत पूर्णांक bnx2x_iov_link_update_vf(काष्ठा bnx2x *bp, पूर्णांक idx) अणुवापस 0; पूर्ण

अटल अंतरभूत पूर्णांक bnx2x_set_vf_link_state(काष्ठा net_device *dev, पूर्णांक vf,
					  पूर्णांक link_state) अणुवापस 0; पूर्ण
काष्ठा pf_vf_bulletin_content;
अटल अंतरभूत व्योम bnx2x_vf_bulletin_finalize(काष्ठा pf_vf_bulletin_content *bulletin,
					      bool support_दीर्घ) अणुपूर्ण

अटल अंतरभूत पूर्णांक bnx2x_vfpf_update_vlan(काष्ठा bnx2x *bp, u16 vid, u8 vf_qid, bool add) अणुवापस 0; पूर्ण

#पूर्ण_अगर /* CONFIG_BNX2X_SRIOV */
#पूर्ण_अगर /* bnx2x_sriov.h */
