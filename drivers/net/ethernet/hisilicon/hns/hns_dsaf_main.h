<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2014-2015 Hisilicon Limited.
 */

#अगर_अघोषित __HNS_DSAF_MAIN_H
#घोषणा __HNS_DSAF_MAIN_H
#समावेश "hnae.h"

#समावेश "hns_dsaf_reg.h"
#समावेश "hns_dsaf_mac.h"

काष्ठा hns_mac_cb;

#घोषणा DSAF_DRV_NAME "hns_dsaf"
#घोषणा DSAF_MOD_VERSION "v1.0"
#घोषणा DSAF_DEVICE_NAME "dsaf"

#घोषणा HNS_DSAF_DEBUG_NW_REG_OFFSET 0x100000

#घोषणा DSAF_BASE_INNER_PORT_NUM 127/* mac tbl qid*/

#घोषणा DSAF_MAX_CHIP_NUM 2  /*max 2 chips */

#घोषणा DSAF_DEFAUTL_QUEUE_NUM_PER_PPE 22

#घोषणा HNS_DSAF_MAX_DESC_CNT 1024
#घोषणा HNS_DSAF_MIN_DESC_CNT 16

#घोषणा DSAF_INVALID_ENTRY_IDX 0xffff

#घोषणा DSAF_CFG_READ_CNT   30

#घोषणा DSAF_DUMP_REGS_NUM 504
#घोषणा DSAF_STATIC_NUM 28
#घोषणा DSAF_V2_STATIC_NUM	44
#घोषणा DSAF_PRIO_NR	8
#घोषणा DSAF_REG_PER_ZONE	3

#घोषणा DSAF_ROCE_CREDIT_CHN	8
#घोषणा DSAF_ROCE_CHAN_MODE	3

#घोषणा HNS_MAX_WAIT_CNT 10000

क्रमागत dsaf_roce_port_mode अणु
	DSAF_ROCE_6PORT_MODE,
	DSAF_ROCE_4PORT_MODE,
	DSAF_ROCE_2PORT_MODE,
	DSAF_ROCE_CHAN_MODE_NUM,
पूर्ण;

क्रमागत dsaf_roce_port_num अणु
	DSAF_ROCE_PORT_0,
	DSAF_ROCE_PORT_1,
	DSAF_ROCE_PORT_2,
	DSAF_ROCE_PORT_3,
	DSAF_ROCE_PORT_4,
	DSAF_ROCE_PORT_5,
पूर्ण;

क्रमागत dsaf_roce_qos_sl अणु
	DSAF_ROCE_SL_0,
	DSAF_ROCE_SL_1,
	DSAF_ROCE_SL_2,
	DSAF_ROCE_SL_3,
पूर्ण;

#घोषणा DSAF_STATS_READ(p, offset) (*((u64 *)((u8 *)(p) + (offset))))
#घोषणा HNS_DSAF_IS_DEBUG(dev) ((dev)->dsaf_mode == DSAF_MODE_DISABLE_SP)

क्रमागत hal_dsaf_mode अणु
	HRD_DSAF_NO_DSAF_MODE	= 0x0,
	HRD_DSAF_MODE		= 0x1,
पूर्ण;

क्रमागत hal_dsaf_tc_mode अणु
	HRD_DSAF_4TC_MODE		= 0X0,
	HRD_DSAF_8TC_MODE		= 0X1,
पूर्ण;

काष्ठा dsaf_vm_def_vlan अणु
	u32 vm_def_vlan_id;
	u32 vm_def_vlan_cfi;
	u32 vm_def_vlan_pri;
पूर्ण;

काष्ठा dsaf_tbl_tcam_data अणु
	u32 tbl_tcam_data_high;
	u32 tbl_tcam_data_low;
पूर्ण;

#घोषणा DSAF_PORT_MSK_NUM \
	((DSAF_TOTAL_QUEUE_NUM + DSAF_SERVICE_NW_NUM - 1) / 32 + 1)
काष्ठा dsaf_tbl_tcam_mcast_cfg अणु
	u8 tbl_mcast_old_en;
	u8 tbl_mcast_item_vld;
	u32 tbl_mcast_port_msk[DSAF_PORT_MSK_NUM];
पूर्ण;

काष्ठा dsaf_tbl_tcam_ucast_cfg अणु
	u32 tbl_ucast_old_en;
	u32 tbl_ucast_item_vld;
	u32 tbl_ucast_mac_discard;
	u32 tbl_ucast_dvc;
	u32 tbl_ucast_out_port;
पूर्ण;

काष्ठा dsaf_tbl_line_cfg अणु
	u32 tbl_line_mac_discard;
	u32 tbl_line_dvc;
	u32 tbl_line_out_port;
पूर्ण;

क्रमागत dsaf_port_rate_mode अणु
	DSAF_PORT_RATE_1000 = 0,
	DSAF_PORT_RATE_2500,
	DSAF_PORT_RATE_10000
पूर्ण;

क्रमागत dsaf_stp_port_type अणु
	DSAF_STP_PORT_TYPE_DISCARD = 0,
	DSAF_STP_PORT_TYPE_BLOCK = 1,
	DSAF_STP_PORT_TYPE_LISTEN = 2,
	DSAF_STP_PORT_TYPE_LEARN = 3,
	DSAF_STP_PORT_TYPE_FORWARD = 4
पूर्ण;

क्रमागत dsaf_sw_port_type अणु
	DSAF_SW_PORT_TYPE_NON_VLAN = 0,
	DSAF_SW_PORT_TYPE_ACCESS = 1,
	DSAF_SW_PORT_TYPE_TRUNK = 2,
पूर्ण;

#घोषणा DSAF_SUB_BASE_SIZE                        (0x10000)

/* dsaf mode define */
क्रमागत dsaf_mode अणु
	DSAF_MODE_INVALID = 0,	/**< Invalid dsaf mode */
	DSAF_MODE_ENABLE_FIX,	/**< en DSAF-mode, fixed to queue*/
	DSAF_MODE_ENABLE_0VM,	/**< en DSAF-mode, support 0 VM */
	DSAF_MODE_ENABLE_8VM,	/**< en DSAF-mode, support 8 VM */
	DSAF_MODE_ENABLE_16VM,	/**< en DSAF-mode, support 16 VM */
	DSAF_MODE_ENABLE_32VM,	/**< en DSAF-mode, support 32 VM */
	DSAF_MODE_ENABLE_128VM,	/**< en DSAF-mode, support 128 VM */
	DSAF_MODE_ENABLE,		/**< beक्रमe is enable DSAF mode*/
	DSAF_MODE_DISABLE_SP,	/* <non-dsaf, single port mode */
	DSAF_MODE_DISABLE_FIX,	/**< non-dasf, fixed to queue*/
	DSAF_MODE_DISABLE_2PORT_8VM,	/**< non-dasf, 2port 8VM */
	DSAF_MODE_DISABLE_2PORT_16VM,	/**< non-dasf, 2port 16VM */
	DSAF_MODE_DISABLE_2PORT_64VM,	/**< non-dasf, 2port 64VM */
	DSAF_MODE_DISABLE_6PORT_0VM,	/**< non-dasf, 6port 0VM */
	DSAF_MODE_DISABLE_6PORT_2VM,	/**< non-dasf, 6port 2VM */
	DSAF_MODE_DISABLE_6PORT_4VM,	/**< non-dasf, 6port 4VM */
	DSAF_MODE_DISABLE_6PORT_16VM,	/**< non-dasf, 6port 16VM */
	DSAF_MODE_MAX		/**< the last one, use as the num */
पूर्ण;

#घोषणा DSAF_DEST_PORT_NUM 256	/* DSAF max port num */
#घोषणा DSAF_WORD_BIT_CNT 32  /* the num bit of word */

/*mac entry, mc or uc entry*/
काष्ठा dsaf_drv_mac_single_dest_entry अणु
	/* mac addr, match the entry*/
	u8 addr[ETH_ALEN];
	u16 in_vlan_id; /* value of VlanId */

	/* the vld input port num, dsaf-mode fix 0, */
	/*	non-dasf is the entry whitch port vld*/
	u8 in_port_num;

	u8 port_num; /*output port num*/
	u8 rsv[6];
पूर्ण;

/*only mc entry*/
काष्ठा dsaf_drv_mac_multi_dest_entry अणु
	/* mac addr, match the entry*/
	u8 addr[ETH_ALEN];
	u16 in_vlan_id;
	/* this mac addr output port,*/
	/*	bit0-bit5 means Port0-Port5(1bit is vld)**/
	u32 port_mask[DSAF_DEST_PORT_NUM / DSAF_WORD_BIT_CNT];

	/* the vld input port num, dsaf-mode fix 0,*/
	/*	non-dasf is the entry whitch port vld*/
	u8 in_port_num;
	u8 rsv[7];
पूर्ण;

काष्ठा dsaf_hw_stats अणु
	u64 pad_drop;
	u64 man_pkts;
	u64 rx_pkts;
	u64 rx_pkt_id;
	u64 rx_छोड़ो_frame;
	u64 release_buf_num;
	u64 sbm_drop;
	u64 crc_false;
	u64 bp_drop;
	u64 rslt_drop;
	u64 local_addr_false;
	u64 vlan_drop;
	u64 stp_drop;
	u64 rx_pfc[DSAF_PRIO_NR];
	u64 tx_pfc[DSAF_PRIO_NR];
	u64 tx_pkts;
पूर्ण;

काष्ठा hnae_vf_cb अणु
	u8 port_index;
	काष्ठा hns_mac_cb *mac_cb;
	काष्ठा dsaf_device *dsaf_dev;
	काष्ठा hnae_handle  ae_handle; /* must be the last number */
पूर्ण;

काष्ठा dsaf_पूर्णांक_xge_src अणु
	u32    xid_xge_ecc_err_पूर्णांक_src;
	u32    xid_xge_fsm_timout_पूर्णांक_src;
	u32    sbm_xge_lnk_fsm_timout_पूर्णांक_src;
	u32    sbm_xge_lnk_ecc_2bit_पूर्णांक_src;
	u32    sbm_xge_mib_req_failed_पूर्णांक_src;
	u32    sbm_xge_mib_req_fsm_timout_पूर्णांक_src;
	u32    sbm_xge_mib_rels_fsm_timout_पूर्णांक_src;
	u32    sbm_xge_sram_ecc_2bit_पूर्णांक_src;
	u32    sbm_xge_mib_buf_sum_err_पूर्णांक_src;
	u32    sbm_xge_mib_req_extra_पूर्णांक_src;
	u32    sbm_xge_mib_rels_extra_पूर्णांक_src;
	u32    voq_xge_start_to_over_0_पूर्णांक_src;
	u32    voq_xge_start_to_over_1_पूर्णांक_src;
	u32    voq_xge_ecc_err_पूर्णांक_src;
पूर्ण;

काष्ठा dsaf_पूर्णांक_ppe_src अणु
	u32    xid_ppe_fsm_timout_पूर्णांक_src;
	u32    sbm_ppe_lnk_fsm_timout_पूर्णांक_src;
	u32    sbm_ppe_lnk_ecc_2bit_पूर्णांक_src;
	u32    sbm_ppe_mib_req_failed_पूर्णांक_src;
	u32    sbm_ppe_mib_req_fsm_timout_पूर्णांक_src;
	u32    sbm_ppe_mib_rels_fsm_timout_पूर्णांक_src;
	u32    sbm_ppe_sram_ecc_2bit_पूर्णांक_src;
	u32    sbm_ppe_mib_buf_sum_err_पूर्णांक_src;
	u32    sbm_ppe_mib_req_extra_पूर्णांक_src;
	u32    sbm_ppe_mib_rels_extra_पूर्णांक_src;
	u32    voq_ppe_start_to_over_0_पूर्णांक_src;
	u32    voq_ppe_ecc_err_पूर्णांक_src;
	u32    xod_ppe_fअगरo_rd_empty_पूर्णांक_src;
	u32    xod_ppe_fअगरo_wr_full_पूर्णांक_src;
पूर्ण;

काष्ठा dsaf_पूर्णांक_rocee_src अणु
	u32    xid_rocee_fsm_timout_पूर्णांक_src;
	u32    sbm_rocee_lnk_fsm_timout_पूर्णांक_src;
	u32    sbm_rocee_lnk_ecc_2bit_पूर्णांक_src;
	u32    sbm_rocee_mib_req_failed_पूर्णांक_src;
	u32    sbm_rocee_mib_req_fsm_timout_पूर्णांक_src;
	u32    sbm_rocee_mib_rels_fsm_timout_पूर्णांक_src;
	u32    sbm_rocee_sram_ecc_2bit_पूर्णांक_src;
	u32    sbm_rocee_mib_buf_sum_err_पूर्णांक_src;
	u32    sbm_rocee_mib_req_extra_पूर्णांक_src;
	u32    sbm_rocee_mib_rels_extra_पूर्णांक_src;
	u32    voq_rocee_start_to_over_0_पूर्णांक_src;
	u32    voq_rocee_ecc_err_पूर्णांक_src;
पूर्ण;

काष्ठा dsaf_पूर्णांक_tbl_src अणु
	u32    tbl_da0_mis_src;
	u32    tbl_da1_mis_src;
	u32    tbl_da2_mis_src;
	u32    tbl_da3_mis_src;
	u32    tbl_da4_mis_src;
	u32    tbl_da5_mis_src;
	u32    tbl_da6_mis_src;
	u32    tbl_da7_mis_src;
	u32    tbl_sa_mis_src;
	u32    tbl_old_sech_end_src;
	u32    lram_ecc_err1_src;
	u32    lram_ecc_err2_src;
	u32    tram_ecc_err1_src;
	u32    tram_ecc_err2_src;
	u32    tbl_ucast_bcast_xge0_src;
	u32    tbl_ucast_bcast_xge1_src;
	u32    tbl_ucast_bcast_xge2_src;
	u32    tbl_ucast_bcast_xge3_src;
	u32    tbl_ucast_bcast_xge4_src;
	u32    tbl_ucast_bcast_xge5_src;
	u32    tbl_ucast_bcast_ppe_src;
	u32    tbl_ucast_bcast_rocee_src;
पूर्ण;

काष्ठा dsaf_पूर्णांक_stat अणु
	काष्ठा dsaf_पूर्णांक_xge_src dsaf_पूर्णांक_xge_stat[DSAF_COMM_CHN];
	काष्ठा dsaf_पूर्णांक_ppe_src dsaf_पूर्णांक_ppe_stat[DSAF_COMM_CHN];
	काष्ठा dsaf_पूर्णांक_rocee_src dsaf_पूर्णांक_rocee_stat[DSAF_COMM_CHN];
	काष्ठा dsaf_पूर्णांक_tbl_src dsaf_पूर्णांक_tbl_stat[1];

पूर्ण;

काष्ठा dsaf_misc_op अणु
	व्योम (*cpld_set_led)(काष्ठा hns_mac_cb *mac_cb, पूर्णांक link_status,
			     u16 speed, पूर्णांक data);
	व्योम (*cpld_reset_led)(काष्ठा hns_mac_cb *mac_cb);
	पूर्णांक (*cpld_set_led_id)(काष्ठा hns_mac_cb *mac_cb,
			       क्रमागत hnae_led_state status);
	/* reset series function, it will be reset अगर the dereset is 0 */
	व्योम (*dsaf_reset)(काष्ठा dsaf_device *dsaf_dev, bool dereset);
	व्योम (*xge_srst)(काष्ठा dsaf_device *dsaf_dev, u32 port, bool dereset);
	व्योम (*ge_srst)(काष्ठा dsaf_device *dsaf_dev, u32 port, bool dereset);
	व्योम (*ppe_srst)(काष्ठा dsaf_device *dsaf_dev, u32 port, bool dereset);
	व्योम (*ppe_comm_srst)(काष्ठा dsaf_device *dsaf_dev, bool dereset);
	व्योम (*hns_dsaf_srst_chns)(काष्ठा dsaf_device *dsaf_dev, u32 msk,
				   bool dereset);
	व्योम (*hns_dsaf_roce_srst)(काष्ठा dsaf_device *dsaf_dev, bool dereset);

	phy_पूर्णांकerface_t (*get_phy_अगर)(काष्ठा hns_mac_cb *mac_cb);
	पूर्णांक (*get_sfp_prsnt)(काष्ठा hns_mac_cb *mac_cb, पूर्णांक *sfp_prsnt);

	पूर्णांक (*cfg_serdes_loopback)(काष्ठा hns_mac_cb *mac_cb, bool en);
पूर्ण;

/* Dsaf device काष्ठा define ,and mac ->  dsaf */
काष्ठा dsaf_device अणु
	काष्ठा device *dev;
	काष्ठा hnae_ae_dev ae_dev;

	u8 __iomem *sc_base;
	u8 __iomem *sds_base;
	u8 __iomem *ppe_base;
	u8 __iomem *io_base;
	काष्ठा regmap *sub_ctrl;
	phys_addr_t ppe_paddr;

	u32 desc_num; /*  desc num per queue*/
	u32 buf_size; /*  ring buffer size */
	u32 reset_offset; /* reset field offset in sub sysctrl */
	पूर्णांक buf_माप_प्रकारype; /* ring buffer size-type */
	क्रमागत dsaf_mode dsaf_mode;	 /* dsaf mode  */
	क्रमागत hal_dsaf_mode dsaf_en;
	क्रमागत hal_dsaf_tc_mode dsaf_tc_mode;
	u32 dsaf_ver;
	u16 tcam_max_num;	/* max TCAM entry क्रम user except promisc */

	काष्ठा ppe_common_cb *ppe_common[DSAF_COMM_DEV_NUM];
	काष्ठा rcb_common_cb *rcb_common[DSAF_COMM_DEV_NUM];
	काष्ठा hns_mac_cb *mac_cb[DSAF_MAX_PORT_NUM];
	काष्ठा dsaf_misc_op *misc_op;

	काष्ठा dsaf_hw_stats hw_stats[DSAF_NODE_NUM];
	काष्ठा dsaf_पूर्णांक_stat पूर्णांक_stat;
	/* make sure tcam table config spinlock */
	spinlock_t tcam_lock;
पूर्ण;

अटल अंतरभूत व्योम *hns_dsaf_dev_priv(स्थिर काष्ठा dsaf_device *dsaf_dev)
अणु
	वापस (व्योम *)((u8 *)dsaf_dev + माप(*dsaf_dev));
पूर्ण

#घोषणा DSAF_TBL_TCAM_KEY_PORT_S 0
#घोषणा DSAF_TBL_TCAM_KEY_PORT_M (((1ULL << 4) - 1) << 0)
#घोषणा DSAF_TBL_TCAM_KEY_VLAN_S 4
#घोषणा DSAF_TBL_TCAM_KEY_VLAN_M (((1ULL << 12) - 1) << 4)

काष्ठा dsaf_drv_tbl_tcam_key अणु
	जोड़ अणु
		काष्ठा अणु
			u8 mac_3;
			u8 mac_2;
			u8 mac_1;
			u8 mac_0;
		पूर्ण bits;

		u32 val;
	पूर्ण high;
	जोड़ अणु
		काष्ठा अणु
			u16 port_vlan;
			u8 mac_5;
			u8 mac_4;
		पूर्ण bits;

		u32 val;
	पूर्ण low;
पूर्ण;

काष्ठा dsaf_drv_soft_mac_tbl अणु
	काष्ठा dsaf_drv_tbl_tcam_key tcam_key;
	u16 index; /*the entry's index in tcam tab*/
पूर्ण;

काष्ठा dsaf_drv_priv अणु
	/* soft tab Mac key, क्रम hardware tab*/
	काष्ठा dsaf_drv_soft_mac_tbl *soft_mac_tbl;
पूर्ण;

अटल अंतरभूत व्योम hns_dsaf_tbl_tcam_addr_cfg(काष्ठा dsaf_device *dsaf_dev,
					      u32 tab_tcam_addr)
अणु
	dsaf_set_dev_field(dsaf_dev, DSAF_TBL_TCAM_ADDR_0_REG,
			   DSAF_TBL_TCAM_ADDR_M, DSAF_TBL_TCAM_ADDR_S,
			   tab_tcam_addr);
पूर्ण

अटल अंतरभूत व्योम hns_dsaf_tbl_tcam_load_pul(काष्ठा dsaf_device *dsaf_dev)
अणु
	u32 o_tbl_pul;

	o_tbl_pul = dsaf_पढ़ो_dev(dsaf_dev, DSAF_TBL_PUL_0_REG);
	dsaf_set_bit(o_tbl_pul, DSAF_TBL_PUL_TCAM_LOAD_S, 1);
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_PUL_0_REG, o_tbl_pul);
	dsaf_set_bit(o_tbl_pul, DSAF_TBL_PUL_TCAM_LOAD_S, 0);
	dsaf_ग_लिखो_dev(dsaf_dev, DSAF_TBL_PUL_0_REG, o_tbl_pul);
पूर्ण

अटल अंतरभूत व्योम hns_dsaf_tbl_line_addr_cfg(काष्ठा dsaf_device *dsaf_dev,
					      u32 tab_line_addr)
अणु
	dsaf_set_dev_field(dsaf_dev, DSAF_TBL_LINE_ADDR_0_REG,
			   DSAF_TBL_LINE_ADDR_M, DSAF_TBL_LINE_ADDR_S,
			   tab_line_addr);
पूर्ण

अटल अंतरभूत काष्ठा hnae_vf_cb *hns_ae_get_vf_cb(
	काष्ठा hnae_handle *handle)
अणु
	वापस container_of(handle, काष्ठा hnae_vf_cb, ae_handle);
पूर्ण

पूर्णांक hns_dsaf_set_mac_uc_entry(काष्ठा dsaf_device *dsaf_dev,
			      काष्ठा dsaf_drv_mac_single_dest_entry *mac_entry);
पूर्णांक hns_dsaf_add_mac_mc_port(काष्ठा dsaf_device *dsaf_dev,
			     काष्ठा dsaf_drv_mac_single_dest_entry *mac_entry);
पूर्णांक hns_dsaf_del_mac_entry(काष्ठा dsaf_device *dsaf_dev, u16 vlan_id,
			   u8 in_port_num, u8 *addr);
पूर्णांक hns_dsaf_del_mac_mc_port(काष्ठा dsaf_device *dsaf_dev,
			     काष्ठा dsaf_drv_mac_single_dest_entry *mac_entry);
व्योम hns_dsaf_fix_mac_mode(काष्ठा hns_mac_cb *mac_cb);

पूर्णांक hns_dsaf_ae_init(काष्ठा dsaf_device *dsaf_dev);
व्योम hns_dsaf_ae_uninit(काष्ठा dsaf_device *dsaf_dev);

व्योम hns_dsaf_update_stats(काष्ठा dsaf_device *dsaf_dev, u32 inode_num);

पूर्णांक hns_dsaf_get_sset_count(काष्ठा dsaf_device *dsaf_dev, पूर्णांक stringset);
व्योम hns_dsaf_get_stats(काष्ठा dsaf_device *ddev, u64 *data, पूर्णांक port);
व्योम hns_dsaf_get_strings(पूर्णांक stringset, u8 *data, पूर्णांक port,
			  काष्ठा dsaf_device *dsaf_dev);

व्योम hns_dsaf_get_regs(काष्ठा dsaf_device *ddev, u32 port, व्योम *data);
पूर्णांक hns_dsaf_get_regs_count(व्योम);
व्योम hns_dsaf_set_promisc_mode(काष्ठा dsaf_device *dsaf_dev, u32 en);
व्योम hns_dsaf_set_promisc_tcam(काष्ठा dsaf_device *dsaf_dev,
			       u32 port, bool enable);

व्योम hns_dsaf_get_rx_mac_छोड़ो_en(काष्ठा dsaf_device *dsaf_dev, पूर्णांक mac_id,
				  u32 *en);
पूर्णांक hns_dsaf_set_rx_mac_छोड़ो_en(काष्ठा dsaf_device *dsaf_dev, पूर्णांक mac_id,
				 u32 en);
पूर्णांक hns_dsaf_rm_mac_addr(
	काष्ठा dsaf_device *dsaf_dev,
	काष्ठा dsaf_drv_mac_single_dest_entry *mac_entry);

पूर्णांक hns_dsaf_clr_mac_mc_port(काष्ठा dsaf_device *dsaf_dev,
			     u8 mac_id, u8 port_num);
पूर्णांक hns_dsaf_रुको_pkt_clean(काष्ठा dsaf_device *dsaf_dev, पूर्णांक port);

पूर्णांक hns_dsaf_roce_reset(काष्ठा fwnode_handle *dsaf_fwnode, bool dereset);

#पूर्ण_अगर /* __HNS_DSAF_MAIN_H__ */
