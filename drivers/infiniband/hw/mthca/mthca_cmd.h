<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2006 Cisco Systems.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित MTHCA_CMD_H
#घोषणा MTHCA_CMD_H

#समावेश <rdma/ib_verbs.h>

#घोषणा MTHCA_MAILBOX_SIZE 4096

क्रमागत अणु
	/* command completed successfully: */
	MTHCA_CMD_STAT_OK 	      = 0x00,
	/* Internal error (such as a bus error) occurred जबतक processing command: */
	MTHCA_CMD_STAT_INTERNAL_ERR   = 0x01,
	/* Operation/command not supported or opcode modअगरier not supported: */
	MTHCA_CMD_STAT_BAD_OP 	      = 0x02,
	/* Parameter not supported or parameter out of range: */
	MTHCA_CMD_STAT_BAD_PARAM      = 0x03,
	/* System not enabled or bad प्रणाली state: */
	MTHCA_CMD_STAT_BAD_SYS_STATE  = 0x04,
	/* Attempt to access reserved or unallocaterd resource: */
	MTHCA_CMD_STAT_BAD_RESOURCE   = 0x05,
	/* Requested resource is currently executing a command, or is otherwise busy: */
	MTHCA_CMD_STAT_RESOURCE_BUSY  = 0x06,
	/* memory error: */
	MTHCA_CMD_STAT_DDR_MEM_ERR    = 0x07,
	/* Required capability exceeds device limits: */
	MTHCA_CMD_STAT_EXCEED_LIM     = 0x08,
	/* Resource is not in the appropriate state or ownership: */
	MTHCA_CMD_STAT_BAD_RES_STATE  = 0x09,
	/* Index out of range: */
	MTHCA_CMD_STAT_BAD_INDEX      = 0x0a,
	/* FW image corrupted: */
	MTHCA_CMD_STAT_BAD_NVMEM      = 0x0b,
	/* Attempt to modअगरy a QP/EE which is not in the presumed state: */
	MTHCA_CMD_STAT_BAD_QPEE_STATE = 0x10,
	/* Bad segment parameters (Address/Size): */
	MTHCA_CMD_STAT_BAD_SEG_PARAM  = 0x20,
	/* Memory Region has Memory Winकरोws bound to: */
	MTHCA_CMD_STAT_REG_BOUND      = 0x21,
	/* HCA local attached memory not present: */
	MTHCA_CMD_STAT_LAM_NOT_PRE    = 0x22,
	/* Bad management packet (silently discarded): */
	MTHCA_CMD_STAT_BAD_PKT 	      = 0x30,
	/* More outstanding CQEs in CQ than new CQ size: */
	MTHCA_CMD_STAT_BAD_SIZE       = 0x40
पूर्ण;

क्रमागत अणु
	MTHCA_TRANS_INVALID = 0,
	MTHCA_TRANS_RST2INIT,
	MTHCA_TRANS_INIT2INIT,
	MTHCA_TRANS_INIT2RTR,
	MTHCA_TRANS_RTR2RTS,
	MTHCA_TRANS_RTS2RTS,
	MTHCA_TRANS_SQERR2RTS,
	MTHCA_TRANS_ANY2ERR,
	MTHCA_TRANS_RTS2SQD,
	MTHCA_TRANS_SQD2SQD,
	MTHCA_TRANS_SQD2RTS,
	MTHCA_TRANS_ANY2RST,
पूर्ण;

क्रमागत अणु
	DEV_LIM_FLAG_RC                 = 1 << 0,
	DEV_LIM_FLAG_UC                 = 1 << 1,
	DEV_LIM_FLAG_UD                 = 1 << 2,
	DEV_LIM_FLAG_RD                 = 1 << 3,
	DEV_LIM_FLAG_RAW_IPV6           = 1 << 4,
	DEV_LIM_FLAG_RAW_ETHER          = 1 << 5,
	DEV_LIM_FLAG_SRQ                = 1 << 6,
	DEV_LIM_FLAG_IPOIB_CSUM		= 1 << 7,
	DEV_LIM_FLAG_BAD_PKEY_CNTR      = 1 << 8,
	DEV_LIM_FLAG_BAD_QKEY_CNTR      = 1 << 9,
	DEV_LIM_FLAG_MW                 = 1 << 16,
	DEV_LIM_FLAG_AUTO_PATH_MIG      = 1 << 17,
	DEV_LIM_FLAG_ATOMIC             = 1 << 18,
	DEV_LIM_FLAG_RAW_MULTI          = 1 << 19,
	DEV_LIM_FLAG_UD_AV_PORT_ENFORCE = 1 << 20,
	DEV_LIM_FLAG_UD_MULTI           = 1 << 21,
पूर्ण;

काष्ठा mthca_mailbox अणु
	dma_addr_t dma;
	व्योम      *buf;
पूर्ण;

काष्ठा mthca_dev_lim अणु
	पूर्णांक max_srq_sz;
	पूर्णांक max_qp_sz;
	पूर्णांक reserved_qps;
	पूर्णांक max_qps;
	पूर्णांक reserved_srqs;
	पूर्णांक max_srqs;
	पूर्णांक reserved_eecs;
	पूर्णांक max_eecs;
	पूर्णांक max_cq_sz;
	पूर्णांक reserved_cqs;
	पूर्णांक max_cqs;
	पूर्णांक max_mpts;
	पूर्णांक reserved_eqs;
	पूर्णांक max_eqs;
	पूर्णांक reserved_mtts;
	पूर्णांक max_mrw_sz;
	पूर्णांक reserved_mrws;
	पूर्णांक max_mtt_seg;
	पूर्णांक max_requester_per_qp;
	पूर्णांक max_responder_per_qp;
	पूर्णांक max_rdma_global;
	पूर्णांक local_ca_ack_delay;
	पूर्णांक max_mtu;
	पूर्णांक max_port_width;
	पूर्णांक max_vl;
	पूर्णांक num_ports;
	पूर्णांक max_gids;
	u16 stat_rate_support;
	पूर्णांक max_pkeys;
	u32 flags;
	पूर्णांक reserved_uars;
	पूर्णांक uar_size;
	पूर्णांक min_page_sz;
	पूर्णांक max_sg;
	पूर्णांक max_desc_sz;
	पूर्णांक max_qp_per_mcg;
	पूर्णांक reserved_mgms;
	पूर्णांक max_mcgs;
	पूर्णांक reserved_pds;
	पूर्णांक max_pds;
	पूर्णांक reserved_rdds;
	पूर्णांक max_rdds;
	पूर्णांक eec_entry_sz;
	पूर्णांक qpc_entry_sz;
	पूर्णांक eeec_entry_sz;
	पूर्णांक eqpc_entry_sz;
	पूर्णांक eqc_entry_sz;
	पूर्णांक cqc_entry_sz;
	पूर्णांक srq_entry_sz;
	पूर्णांक uar_scratch_entry_sz;
	पूर्णांक mpt_entry_sz;
	जोड़ अणु
		काष्ठा अणु
			पूर्णांक max_avs;
		पूर्ण tavor;
		काष्ठा अणु
			पूर्णांक resize_srq;
			पूर्णांक max_pbl_sz;
			u8  bmme_flags;
			u32 reserved_lkey;
			पूर्णांक lam_required;
			u64 max_icm_sz;
		पूर्ण arbel;
	पूर्ण hca;
पूर्ण;

काष्ठा mthca_adapter अणु
	u32  venकरोr_id;
	u32  device_id;
	u32  revision_id;
	अक्षर board_id[MTHCA_BOARD_ID_LEN];
	u8   पूर्णांकa_pin;
पूर्ण;

काष्ठा mthca_init_hca_param अणु
	u64 qpc_base;
	u64 eec_base;
	u64 srqc_base;
	u64 cqc_base;
	u64 eqpc_base;
	u64 eeec_base;
	u64 eqc_base;
	u64 rdb_base;
	u64 mc_base;
	u64 mpt_base;
	u64 mtt_base;
	u64 uar_scratch_base;
	u64 uarc_base;
	u16 log_mc_entry_sz;
	u16 mc_hash_sz;
	u8  log_num_qps;
	u8  log_num_eecs;
	u8  log_num_srqs;
	u8  log_num_cqs;
	u8  log_num_eqs;
	u8  log_mc_table_sz;
	u8  mtt_seg_sz;
	u8  log_mpt_sz;
	u8  log_uar_sz;
	u8  log_uarc_sz;
पूर्ण;

काष्ठा mthca_init_ib_param अणु
	पूर्णांक port_width;
	पूर्णांक vl_cap;
	पूर्णांक mtu_cap;
	u16 gid_cap;
	u16 pkey_cap;
	पूर्णांक set_guid0;
	u64 guid0;
	पूर्णांक set_node_guid;
	u64 node_guid;
	पूर्णांक set_si_guid;
	u64 si_guid;
पूर्ण;

काष्ठा mthca_set_ib_param अणु
	पूर्णांक set_si_guid;
	पूर्णांक reset_qkey_viol;
	u64 si_guid;
	u32 cap_mask;
पूर्ण;

पूर्णांक mthca_cmd_init(काष्ठा mthca_dev *dev);
व्योम mthca_cmd_cleanup(काष्ठा mthca_dev *dev);
पूर्णांक mthca_cmd_use_events(काष्ठा mthca_dev *dev);
व्योम mthca_cmd_use_polling(काष्ठा mthca_dev *dev);
व्योम mthca_cmd_event(काष्ठा mthca_dev *dev, u16 token,
		     u8  status, u64 out_param);

काष्ठा mthca_mailbox *mthca_alloc_mailbox(काष्ठा mthca_dev *dev,
					  gfp_t gfp_mask);
व्योम mthca_मुक्त_mailbox(काष्ठा mthca_dev *dev, काष्ठा mthca_mailbox *mailbox);

पूर्णांक mthca_SYS_EN(काष्ठा mthca_dev *dev);
पूर्णांक mthca_SYS_DIS(काष्ठा mthca_dev *dev);
पूर्णांक mthca_MAP_FA(काष्ठा mthca_dev *dev, काष्ठा mthca_icm *icm);
पूर्णांक mthca_UNMAP_FA(काष्ठा mthca_dev *dev);
पूर्णांक mthca_RUN_FW(काष्ठा mthca_dev *dev);
पूर्णांक mthca_QUERY_FW(काष्ठा mthca_dev *dev);
पूर्णांक mthca_ENABLE_LAM(काष्ठा mthca_dev *dev);
पूर्णांक mthca_DISABLE_LAM(काष्ठा mthca_dev *dev);
पूर्णांक mthca_QUERY_DDR(काष्ठा mthca_dev *dev);
पूर्णांक mthca_QUERY_DEV_LIM(काष्ठा mthca_dev *dev,
			काष्ठा mthca_dev_lim *dev_lim);
पूर्णांक mthca_QUERY_ADAPTER(काष्ठा mthca_dev *dev,
			काष्ठा mthca_adapter *adapter);
पूर्णांक mthca_INIT_HCA(काष्ठा mthca_dev *dev,
		   काष्ठा mthca_init_hca_param *param);
पूर्णांक mthca_INIT_IB(काष्ठा mthca_dev *dev,
		  काष्ठा mthca_init_ib_param *param,
		  पूर्णांक port);
पूर्णांक mthca_CLOSE_IB(काष्ठा mthca_dev *dev, पूर्णांक port);
पूर्णांक mthca_CLOSE_HCA(काष्ठा mthca_dev *dev, पूर्णांक panic);
पूर्णांक mthca_SET_IB(काष्ठा mthca_dev *dev, काष्ठा mthca_set_ib_param *param,
		 पूर्णांक port);
पूर्णांक mthca_MAP_ICM(काष्ठा mthca_dev *dev, काष्ठा mthca_icm *icm, u64 virt);
पूर्णांक mthca_MAP_ICM_page(काष्ठा mthca_dev *dev, u64 dma_addr, u64 virt);
पूर्णांक mthca_UNMAP_ICM(काष्ठा mthca_dev *dev, u64 virt, u32 page_count);
पूर्णांक mthca_MAP_ICM_AUX(काष्ठा mthca_dev *dev, काष्ठा mthca_icm *icm);
पूर्णांक mthca_UNMAP_ICM_AUX(काष्ठा mthca_dev *dev);
पूर्णांक mthca_SET_ICM_SIZE(काष्ठा mthca_dev *dev, u64 icm_size, u64 *aux_pages);
पूर्णांक mthca_SW2HW_MPT(काष्ठा mthca_dev *dev, काष्ठा mthca_mailbox *mailbox,
		    पूर्णांक mpt_index);
पूर्णांक mthca_HW2SW_MPT(काष्ठा mthca_dev *dev, काष्ठा mthca_mailbox *mailbox,
		    पूर्णांक mpt_index);
पूर्णांक mthca_WRITE_MTT(काष्ठा mthca_dev *dev, काष्ठा mthca_mailbox *mailbox,
		    पूर्णांक num_mtt);
पूर्णांक mthca_SYNC_TPT(काष्ठा mthca_dev *dev);
पूर्णांक mthca_MAP_EQ(काष्ठा mthca_dev *dev, u64 event_mask, पूर्णांक unmap,
		 पूर्णांक eq_num);
पूर्णांक mthca_SW2HW_EQ(काष्ठा mthca_dev *dev, काष्ठा mthca_mailbox *mailbox,
		   पूर्णांक eq_num);
पूर्णांक mthca_HW2SW_EQ(काष्ठा mthca_dev *dev, काष्ठा mthca_mailbox *mailbox,
		   पूर्णांक eq_num);
पूर्णांक mthca_SW2HW_CQ(काष्ठा mthca_dev *dev, काष्ठा mthca_mailbox *mailbox,
		   पूर्णांक cq_num);
पूर्णांक mthca_HW2SW_CQ(काष्ठा mthca_dev *dev, काष्ठा mthca_mailbox *mailbox,
		   पूर्णांक cq_num);
पूर्णांक mthca_RESIZE_CQ(काष्ठा mthca_dev *dev, पूर्णांक cq_num, u32 lkey, u8 log_size);
पूर्णांक mthca_SW2HW_SRQ(काष्ठा mthca_dev *dev, काष्ठा mthca_mailbox *mailbox,
		    पूर्णांक srq_num);
पूर्णांक mthca_HW2SW_SRQ(काष्ठा mthca_dev *dev, काष्ठा mthca_mailbox *mailbox,
		    पूर्णांक srq_num);
पूर्णांक mthca_QUERY_SRQ(काष्ठा mthca_dev *dev, u32 num,
		    काष्ठा mthca_mailbox *mailbox);
पूर्णांक mthca_ARM_SRQ(काष्ठा mthca_dev *dev, पूर्णांक srq_num, पूर्णांक limit);
पूर्णांक mthca_MODIFY_QP(काष्ठा mthca_dev *dev, क्रमागत ib_qp_state cur,
		    क्रमागत ib_qp_state next, u32 num, पूर्णांक is_ee,
		    काष्ठा mthca_mailbox *mailbox, u32 opपंचांगask);
पूर्णांक mthca_QUERY_QP(काष्ठा mthca_dev *dev, u32 num, पूर्णांक is_ee,
		   काष्ठा mthca_mailbox *mailbox);
पूर्णांक mthca_CONF_SPECIAL_QP(काष्ठा mthca_dev *dev, पूर्णांक type, u32 qpn);
पूर्णांक mthca_MAD_IFC(काष्ठा mthca_dev *dev, पूर्णांक ignore_mkey, पूर्णांक ignore_bkey,
		  पूर्णांक port, स्थिर काष्ठा ib_wc *in_wc, स्थिर काष्ठा ib_grh *in_grh,
		  स्थिर व्योम *in_mad, व्योम *response_mad);
पूर्णांक mthca_READ_MGM(काष्ठा mthca_dev *dev, पूर्णांक index,
		   काष्ठा mthca_mailbox *mailbox);
पूर्णांक mthca_WRITE_MGM(काष्ठा mthca_dev *dev, पूर्णांक index,
		    काष्ठा mthca_mailbox *mailbox);
पूर्णांक mthca_MGID_HASH(काष्ठा mthca_dev *dev, काष्ठा mthca_mailbox *mailbox,
		    u16 *hash);
पूर्णांक mthca_NOP(काष्ठा mthca_dev *dev);

#पूर्ण_अगर /* MTHCA_CMD_H */
